# capstone library name (without prefix 'lib' and suffix '.so')
LIBNAME = capstone
<<<<<<< HEAD
CXXHEADERS = -std=c++1y -I. -Wall -Wno-reorder

%.o: %.cpp %.h
	${CXX} -c $< -o $@ $(CXXHEADERS)
	
all: main.cpp *.o heuristics/*.o
	${CXX} -g $^ -o main $(CXXHEADERS) -l$(LIBNAME)

clean:
	rm heuristics/*.o *.o main
=======
CXXHEADERS = -std=c++1y -Wall

#captest: captest.o
#	${CXX} $< -O3 -Wall -l$(LIBNAME) -o $@

%.o: %.cpp %.h
	${CXX} -c $< -o $@ $(CXXHEADERS)
	
all: main.cpp *.o
	${CXX} -g $^ -o main $(CXXHEADERS) -l$(LIBNAME)

clean:
	rm *.o main
>>>>>>> 0bd8beca2410f242e8beec6e1df1149a0692e11a
