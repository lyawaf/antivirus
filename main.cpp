#include <iostream>
#include <fstream>
#include <cstring>
#include <stdexcept>

extern "C"
{
	#include <capstone/capstone.h>
}


enum filetype
{
	PE = 0,
	ELF,
	DAFUCK
};

using namespace std;

filetype determineFiletype(ifstream &);

int main(int argc, char** argv)
{
	ifstream binary;

	if (argc < 3)
		throw runtime_error("Not enough arguments");

	for (int i = 2; i < argc; i++)
	{	
		if (strtoul(argv[i], NULL, 0) == 0)
			throw runtime_error("Invalid address");
	}

	binary.open(argv[1]);
	
	if (binary.is_open())
	{
		filetype type = determineFiletype(binary);
		switch(type)
		{
			case PE:
				//TODO handlers
				break;
			case ELF:
				//also TODO handlers
				break;
			default:
				throw runtime_error("Unknown filetype");
		}
	}
	else
		throw runtime_error("Unable to open file");

	binary.close();

	return 0;
}

filetype determineFiletype(ifstream &bin)
{	
	char type[4];
	bin.read(type, 4);

	if (strncmp(type, "\x7F\x45\x4C\x46", 4) == 0) //if 4 bytes == ".ELF"
	{
		return ELF;
	}
	else if(strncmp(type, "MZ", 2) == 0) 
	{
		return PE;
	}

	return DAFUCK;
}