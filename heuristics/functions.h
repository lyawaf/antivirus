//This file includes all heuristics functions,
//embraces them all into an array && provides a way
//to execute them to get the answer

enum CCTypes
{
	cdecl,
	stdcall,
	msfastcall,
	none
};
//the above values are return types for heuristic functions
//those functions are of type OneStepDisasm -> CCTypes

//following lines are inclusion of heuristic functions. 
//They are included automatically with ./includefunctions script
//TODO: write the script

//@@INCLUSIONS
//@@END

//following lines define an array of lambdas that call heuristic functions
//They are inserted automatically with ./includefunctions script

auto heuristicFunctions[] =
{
//@@ARRAY
//@@END
}
