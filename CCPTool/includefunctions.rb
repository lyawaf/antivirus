#!/usr/bin/ruby

#This script looks at every .h file in this directory and makes a heuristic function out of it
#It searches for line "//@@FUNCTION" followed by the line like "CCTypes name"
#whence it takes the name of the function and uses it in functions.cpp
FunctionKeyword = "//@@FUNCTION\n"
IncludeKeyword = "//@@INCLUSIONS\n"
ArrayKeyword = "//@@ARRAY\n"
EndKeyword = "//@@END\n"
SizeKeyword = "//@@SIZE\n"
IgnoreFiles = ["functions.h", "includefunctions"]
SearchDir = "./heuristics/"

def yank_fnname text
	lines = text.each_line.to_a
	fnline = -1

	lines.length.times do |i|
		if lines[i] == FunctionKeyword
			fnline = lines[i+1]
			break
		end
	end

	if fnline == -1
		raise "Function not found"
	end

	fnline.strip!

	words = fnline.split

	if words[0] != "CCTypes"
		raise "Incorrect file format: expected CCTypes, got " + words[0]
	end

	fnname = words[1].split("(")[0] #if there is no space between the bracket and function name

	return fnname
end

if __FILE__ == $0

	unless File.file? "functions.cpp"
		abort "FATAL: no file 'functions.cpp'. Check if you're running the script in the right directory"
	end

	#first we obtain the filenames and function names
	filenames = []
	fnnames = []

	Dir.foreach SearchDir do |filename|
		next if filename == "." or filename == ".." 
		next if filename.split('').last(4).join == ".cpp" #so skip if it's a .cpp file
		next if filename[0] == "." #skip if a hidden file: those usually aren't needed
		next if filename.split('').last(2).join == ".o"   #precompiled fiels also aren't our thing
		next if IgnoreFiles.include? filename #ignore other predetermined files, especially this script and functions.h
		
		full_name = SearchDir + filename
		unless File.file? full_name
			abort "FATAL: could not open file " + full_name
		end

		File.open full_name, "r" do |file|
			begin
				text = file.read
				name = yank_fnname text
				filenames += [full_name]
				fnnames += [name]
			rescue => e
				STDERR.puts "An error occured when parsing file '%s': %s" % [full_name, e.message]
			end
		end
	end

	lines = ""
	#extract the content of functions.cpp ...
	File.open "functions.cpp", "r" do |source| 
		lines = source.read.each_line.to_a
	end
	
	# ...and modify it
	File.open ".functions.swap", "w" do |destination|
		i = 0 #line in source text index
		

		#write the lines of source text to the new text until we meet the first keyword
		while lines[i] != IncludeKeyword
			if i == lines.length
				abort "FATAL: incorrect functions.cpp structure: can't find %s" % IncludeKeyword.strip  
			end
			
			destination.write lines[i]
			i += 1
		end
		#also write the end keyword, it's necessary for future
		destination.write IncludeKeyword

		#now put down all the inclusions
		filenames.each do |name|
			destination.write "#include \"%s\"\n" % name
		end

		#skip till the end of inclusions in source file
		while lines[i] != EndKeyword
			if i == lines.length
				abort "FATAl: incorrect functions.cpp structure: can't find %s after %s" % [ EndKeyword.strip, IncludeKeyword.strip ]
			end

			#skippity skip
			i += 1
		end
		#write down keywordEnd too, it's nessesary
		destination.write EndKeyword; i += 1 #as it was not accounted and we don't want to put it down twice


		#write the lines of source text to the new text until we meet the second keyword
		while lines[i] != ArrayKeyword
			if i == lines.length
				abort "FATAL: incorrect functions.cpp structure: can't find %s after %s" % [ ArrayKeyword.strip, IncludeKeyword.strip ]  
			end
			
			destination.write lines[i]
			i += 1
		end
		#also write the end keyword, it's necessary for future
		destination.write ArrayKeyword

		#now put down all the lambdas, but the last one is treated specifically as it doesn't have a ,
		fnnames[0...-1].each do |name|
			destination.write "	%s,\n" % name
		end
		#and the last one:
		destination.write "	%s\n" % fnnames[-1]
		
		#skip till the end of array in source file
		while lines[i] != EndKeyword
			if i == lines.length
				abort "FATAl: incorrect functions.cpp structure: can't find %s after %s" % [ EndKeyword.strip, ArrayKeyword.strip ]
			end

			#skippity skip
			i += 1
		end
		#write down keywordEnd too, it's nessesary
		destination.write EndKeyword; i += 1 #as it was not accounted and we don't want to put it down twice


		#write the lines of source text to the new text until we meet the third keyword
		while lines[i] != SizeKeyword
			if i == lines.length
				abort "FATAL: incorrect functions.cpp structure: can't find %s after %s" % [ SizeKeyword.strip, ArrayKeyword.strip ]  
			end
			
			destination.write lines[i]
			i += 1
		end
		#also write the end keyword, it's necessary for future
		destination.write SizeKeyword

		#now write down the size of the array
		destination.write "const size_t heuristicFunctionsSize = %d;\n" % fnnames.length

		#skip till the end of size determinition in source file
		while lines[i] != EndKeyword
			if i == lines.length
				abort "FATAL: incorrect functions.cpp structure: can't find %s after %s" % [ EndKeyword.strip, SizeKeyword.strip ]
			end

			#skippity skip
			i += 1
		end
		#write down keywordEnd too, it's nessesary
		destination.write EndKeyword; i += 1 #as it was not accounted and we don't want to put it down twice


		#aand, write the rest of the file too
		while i < lines.length
			destination.write lines[i]
			i += 1
		end
	end

	#cleaning up, because after the above we have two files, with one too old and another with a wrong name
	File.delete "functions.cpp"
	File.rename ".functions.swap", "functions.cpp"
end
