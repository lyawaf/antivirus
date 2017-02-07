#include <iostream>
#include <fstream>
#include <cstring>
#include <stdexcept>

#include <capstone/capstone.h>

#include "wrapper.h"
#include "heuristics/functions.h"


enum filetype
{
	PE = 0,
	ELF,
	DAFUCK
};

using namespace std;

filetype determineFiletype(ifstream &);

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
		OneStepDisasm d {name, 32, 0};

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

filetype determineFiletype(ifstream &bin)
{	
	char type[4];
	bin.read(type, 4);

	if (strncmp(type, "\x7F\x45\x4C\x46", 4) == 0) //if 4 bytes == ".ELF"
	{
		return ELF;
	}
	else if(strncmp(type, "MZ", 2) == 0) 
	{
		return PE;
	}

	return DAFUCK;
}
