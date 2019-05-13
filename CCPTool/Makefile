# capstone library name (without prefix 'lib' and suffix '.so')
LIBNAME = capstone
CXXHEADERS = -std=c++1y -I. -Wall -Wno-reorder

%.o: %.cpp %.h
	${CXX} -c $< -o $@ $(CXXHEADERS)
	
all: main.cpp wrapper.o functions.o heuristics/*.o
	${CXX} -g $^ -o main $(CXXHEADERS) -l$(LIBNAME)

functions.o: functions.h functions.cpp heuristics/*.h includefunctions.rb
	./includefunctions.rb
	${CXX} -c functions.cpp -o functions.o $(CXXHEADERS)

clean:
	rm heuristics/*.o *.o main
