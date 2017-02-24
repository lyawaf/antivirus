#include <iostream>
#include <map>

#include "nikitail.h"

using std::cout;
using std::endl;
using std::hex;
using std::set;


const bool DEBUG = true;


//sets of instructions that should be examined
//with both arguments intresting
set<string> good_doubly_operations {
	 "add", "sub", "dec", "inc", "xor"
};
//with righthand argumant intresting
set<string> good_rightly_operations {
	"mov", "movb"
};

//a function that determines whether set contains element
template <typename T, typename P>
inline bool contains(set<T> s, P elem)
{
	return s.find(elem) != s.end();
}

//a function that given a disassembler will determine the registers used until the ret command or end of disassembly
//first set is registers read, second is registers written
pair< set<x86_reg>, set<x86_reg> > registers_used(OneStepDisasm d)
{
	set<x86_reg> read {};
	set<x86_reg> written {};
	while (true)
	{
		auto instr = d.next();
		if (instr.empty)
			break;

		if (DEBUG)
			cout << "0x" <<hex << instr.address <<"\t\t" <<instr.mnemonic <<"\t" <<instr.operands <<endl;

		if (contains(instr.groups, CS_GRP_JUMP))
		{
			cout << "found a jump command\n";
		}
		else if (contains(instr.groups, CS_GRP_CALL))
		{
			cout << "found a call command\n";
		}
		else if (contains(instr.groups, CS_GRP_RET))
		{
			cout << "found a return command\n";

			if (!DEBUG)
				return make_pair(read, written);
		}
		else
		{
			if contains(good_doubly_operations, instr.)
		}
	}
	return make_pair(read, written);
}

CCTypes nikitailDeterminer(OneStepDisasm d)
{
	auto t = registers_used(d);
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
