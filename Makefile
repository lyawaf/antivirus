# capstone library name (without prefix 'lib' and suffix '.so')
LIBNAME = capstone
CXXHEADERS = -std=c++1y -I. -Wall

%.o: %.cpp %.h
	${CXX} -c $< -o $@ $(CXXHEADERS)
	
all: main.cpp *.o heuristics/*.o
	${CXX} -g $^ -o main $(CXXHEADERS) -l$(LIBNAME)

clean:
	rm heuristics/*.o *.o main
