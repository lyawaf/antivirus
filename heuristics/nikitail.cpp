#include <iostream>
using std::cout;
using std::endl;
using std::hex;

#include "nikitail.h"

CCTypes nikitailDeterminer(OneStepDisasm d)
{
	auto instr = d.next();
//	cout <<"this instruction is " <<instr.empty <<endl;
	cout << "0x" <<hex << instr.address <<"\t\t" <<instr.mnemonic <<"\t" <<instr.operands <<endl;
	while (!instr.empty)
	{
//		cout <<"this instruction is " <<instr.empty <<endl;
		cout << "0x" <<hex << instr.address <<"\t\t" <<instr.mnemonic <<"\t" <<instr.operands <<endl;
		instr = d.next();
	}

	return none;
}
