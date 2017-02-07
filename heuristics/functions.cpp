#include <map>

#include "functions.h"

CCTypes determine(OneStepDisasm disasmer)
{
	std::map<CCTypes, int> weight;

	for (unsigned int i = 0; i < heuristicFunctionsSize; ++i)
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
