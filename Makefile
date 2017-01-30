# capstone library name (without prefix 'lib' and suffix '.so')
LIBNAME = capstone
CXXHEADERS = -std=c++1y -Wall

%.o: %.cpp %.h
	${CXX} -c $< -o $@ $(CXXHEADERS)
	
all: main.cpp *.o
	${CXX} -g $^ -o main $(CXXHEADERS) -l$(LIBNAME)

clean:
	rm *.o main
