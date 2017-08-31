#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <stdexcept>
#include <vector>

#include <capstone/capstone.h>

#include "wrapper.h"
#include "heuristics/functions.h"


using namespace std;

int main(int argc, char** argv)
{
	if (argc < 3)
	{
		cerr <<"Usage: " <<argv[0] <<" FILENAME ADDRESS [ADDRESS ...]" <<endl;
		return 0;
	}
	string name (argv[1]);
	vector<string> addresses (argv + 2, argv + argc);

	for (auto i : addresses)
	{
		try
		{
			auto addr   = stoll(i, nullptr, 16);
			auto v_addr = addr + 0x400000; //a wild guess
			OneStepDisasm d {name, 64, addr, v_addr};

			auto type = determine(d);

			switch (type)
			{
				case cdecl:
					cout << "Function at " << i << ": cdecl" << endl;
					break;
				case stdcall:
					cout << "Function at " << i << ": stdcall" << endl;
					break;
				case msfastcall:
					cout << "Function at " << i << ": msfastcall" << endl;
					break;
				default:
					cout <<"whatever, idc\n";
			}
		}
		catch (const invalid_argument& e)
		{
			cerr << "Could not convert \"" << i << "\"to address: " << e.what() << endl;
		}
		catch (const runtime_error& e)
		{
			cerr << "Exception caught when parsing argument \"" << i "\": " << e.what() <<endl;
		}
	}
}
