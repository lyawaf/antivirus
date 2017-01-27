# capstone library name (without prefix 'lib' and suffix '.so')
LIBNAME = capstone
CXXHEADERS = -std=c++1y -Wall

#captest: captest.o
#	${CXX} $< -O3 -Wall -l$(LIBNAME) -o $@

%.o: %.cpp
	${CXX} -c $< -o $@ $(CXXHEADERS)
	
all: *.o main.cpp
	${CXX} $< -o main $(CXXHEADERS)

clean:
	rm *.o main
