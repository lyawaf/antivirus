#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <stdexcept>
#include <vector>
#include <map>

#include <capstone/capstone.h>

#include "wrapper.h"
#include "functions.h"


using namespace std;

typedef map<string, string> param_map;

//parse argv's arguments of type --name=val to a nice map
pair< param_map, vector<string> > get_parameters(const vector<string>& argv, param_map pars = param_map())
{
	vector<string> others;

	for (auto param : argv)
	{
		if (param.size() > 2 && param[0] == '-' && param[1] == '-')
		{
			auto eq_index = param.find_first_of('=');
			auto name_len = eq_index - 2;
			auto name     = param.substr(2, name_len);
			auto value    = param.substr(eq_index + 1);

			pars[name] = value;
		}
		else
		{
			others.push_back(param);
		}
	}

	return make_pair(pars, others);
}

void print_usage(const char* prgname)
{
	cerr <<"Usage: " <<prgname <<" FILENAME ADDRESS [ADDRESS ...]" <<endl;
	return;
}


int main(int argc, char** __argv)
{
	if (argc < 3)
	{
		print_usage(__argv[0]);
		return 0;
	}
	vector<string> argv (__argv + 1, __argv + argc);
	param_map default_params = {
		{"arch", "32"}
	};
	auto t = get_parameters(argv, default_params);

	auto parameters = t.first;
	auto args       = t.second;

	//parse parameters to useful values
	auto ARCH = stoi(parameters["arch"]);

	//the syntax is that filename comes first
	auto file_name  = args.front();

	//set iteration at second string
	auto iter = args.begin(); ++iter;
	for (; iter != args.end(); ++iter)
	{
		try
		{
			auto addr   = stoull(*iter, nullptr, 16);
			auto v_addr = addr + 0x400000; //a wild guess
			OneStepDisasm d (file_name, ARCH, addr, v_addr);

			auto type = determine(d);

			switch (type)
			{
				case cdecl:
				case stdcall:
				case msfastcall:
					cout << "safe";
					break;
				default:
					cout <<"virus";
					break;
			}
			cout << " signature at function " << *iter << endl
		}
		catch (const invalid_argument& e)
		{
			cerr << "Could not convert \"" << *iter << "\"to address: " << e.what() << endl;
		}
		catch (const bad_alloc& e)
		{
			cerr << "Could not allocate space for file " << file_name << endl;
		}
		catch (const runtime_error& e)
		{
			cerr << "Exception caught when parsing argument \"" << *iter << "\": " << e.what() <<endl;
		}
	}
}
