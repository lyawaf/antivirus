#include <iostream>
#include <map>

#include "nikitail.h"

using std::cout;
using std::endl;
using std::hex;
using std::set;


const bool DEBUG = true;

//a function that given a disassembler will determine the registers used until the ret command or end of disassembly
//first set is registers read, second is registers written
pair< set<x86_reg>, set<x86_reg> > registersUsed(OneStepDisasm d)
{
	set<x86_reg> read {};
	set<x86_reg> written {};
	//if it's a jump or call command..
	while (true)
	{
		auto instr = d.next();

		if (instr.empty)
			break;


		if (DEBUG)
			cout << "0x" <<hex << instr.address <<"\t\t" <<instr.mnemonic <<"\t" <<instr.operands <<endl;

		if (instr.groups.find(CS_GRP_JUMP) != instr.groups.end())
		{
			cout << "found a jump command\n";
		}
		if (instr.groups.find(CS_GRP_CALL) != instr.groups.end())
		{
			cout << "found a call command\n";
		}
		if (instr.groups.find(CS_GRP_RET) != instr.groups.end())
		{
			cout << "found a return command\n";

			if (!DEBUG)
				return make_pair(read, written);
		}
	}
	return make_pair(read, written);
}

CCTypes nikitailDeterminer(OneStepDisasm d)
{
	//do-while doesn't work for some reason, using this with break
	auto t = registersUsed(d);
	auto read = t.first;
	auto written = t.second;

	cout <<"registers read: ";
	for (auto i : read)
		cout <<i <<' ';
	cout <<endl <<"registers written: ";
	for (auto i : written)
		cout <<i <<' ';
	cout <<endl;


	return none;
}
