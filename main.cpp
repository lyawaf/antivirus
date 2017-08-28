#include <iostream>
#include <fstream>
#include <cstring>
#include <stdexcept>

#include <capstone/capstone.h>

#include "wrapper.h"
#include "heuristics/functions.h"


using namespace std;

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		cerr <<"usage: " <<argv[0] <<" filename" <<endl;
		return 0;
	}
	string name {argv[1]};

	try
	{
		uint64_t t = 0xb0;
		OneStepDisasm d {name, 64, t, 0x4000b0};

		auto type = determine(d);

		switch (type)
		{
		default:
			cout <<"whatever, idc\n";
		}
	}
	catch (runtime_error e)
	{
		cerr <<"exception caught: " <<e.what() <<endl;
	}
}
