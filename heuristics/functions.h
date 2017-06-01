#include "../wrapper.h"
#include "../cctypes.h"
//This file includes all heuristics functions,
//embraces them all into an array && provides a way
//to execute them to get the answer


//following lines define an array of pointers to heuristic functions
//They are inserted automatically with ./includefunctions script

extern CCTypes (*heuristicFunctions[]) (OneStepDisasm);

//also as this is pretty much C stuff, it needs a variable to store the size of the array

extern const size_t heuristicFunctionsSize;


CCTypes determine(OneStepDisasm disasmer);
