#include <map>

#include "functions.h"


//following lines are inclusion of heuristic functions. 
//They are included automatically with ./includefunctions script

//@@INCLUSIONS
#include "./heuristics/nikitail.h"
//@@END


CCTypes (*heuristicFunctions[]) (OneStepDisasm) =
{
//@@ARRAY
	nikitailDeterminer
//@@END
};


//@@SIZE
const size_t heuristicFunctionsSize = 1;
//@@END


CCTypes determine(OneStepDisasm disasmer)
{
	std::map<CCTypes, int> weight;

	for (size_t i = 0; i < heuristicFunctionsSize; ++i)
	{
		auto type = heuristicFunctions[i](disasmer);
		weight[type] += 1;
	}

	CCTypes type = none;
	int max = 0;

	for (auto i : weight)
	{
		if ( i.second > max )
		{
			max = i.second;
			type = i.first;
		}
	}

	return type;
}
