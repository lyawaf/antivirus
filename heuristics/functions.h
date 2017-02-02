#include "../wrapper.h"
#include "../cctypes.h"
//This file includes all heuristics functions,
//embraces them all into an array && provides a way
//to execute them to get the answer

//following lines are inclusion of heuristic functions. 
//They are included automatically with ./includefunctions script
//TODO: write the script

//@@INCLUSIONS
//@@END

//following lines define an array of lambdas that call heuristic functions
//They are inserted automatically with ./includefunctions script

CCTypes (*heuristicFunctions[]) (OneStepDisasm) =
{
//@@ARRAY
//@@END
};

//also as this is pretty much C stuff, it needs a variable to store the size of the array

//@@SIZE
const size_t heuristicFunctionsSize = 0;
//@@END

CCTypes determine(OneStepDisasm disasmer);
