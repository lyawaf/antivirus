#include <iostream>
using std::cout;
using std::endl;
using std::hex;

#include "nikitail.h"

CCTypes nikitailDeterminer(OneStepDisasm d)
{
	auto instr = d.next();
	while (!instr.empty)
	{
		cout << "0x" <<hex << instr.address <<"\t\t" <<instr.mnemonic <<"\t" <<instr.operands <<endl;
		instr = d.next();
	}

	return none;
}
