# capstone library name (without prefix 'lib' and suffix '.so')
LIBNAME = capstone

#captest: captest.o
#	${CXX} $< -O3 -Wall -l$(LIBNAME) -o $@

%.o: %.cpp
	${CXX} -c $< -o $@ -std=c++1y

clean:
	rm captest captest.o
