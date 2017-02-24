#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <sstream>

#include "nikitail.h"

using std::cout;
using std::endl;
using std::hex;
using std::set;
using std::vector;
using std::stringstream;
using std::getline;



const bool DEBUG = true;


//a function that splits the string
vector<string> split(string str, const string& delimit)
{
	vector<string> r;
	size_t pos = 0;
	string token;

	while ((pos = str.find(delimit)) != string::npos)
	{
		token = str.substr(0, pos);
		r.push_back(token);
		str.erase(0, pos + delimit.length());
	}
	r.push_back(str);

	return r;
}

//sets of instructions that should be examined
//with both arguments intresting
set<string> good_doubly_operations {
	 "add", "sub", "dec", "inc", "xor"
};
//with righthand argumant intresting
set<string> good_rightly_operations {
	"mov", "movb"
};

//sets for different mnemonics for registers
set<string> ax {
	"eax", "rax", "ax", "al", "ah"
};
set<string> bx {
	"ebx", "rbx", "bx", "bl", "bh"
};
set<string> cx {
	"ecx", "rcx", "cx", "cl", "ch"
};
set<string> dx {
	"edx", "rdx", "dx", "dl", "dh"
};
set<string> di {
	"rdi", "edi", "di"
};
set<string> si {
	"rsi", "esi", "si"
};
set<string> r8 {
	"r8"
};
set<string> r9 {
	"r9"
};
//
//a function that determines whether set contains element
template <typename T, typename P>
inline bool contains(set<T> s, P elem)
{
	return s.find(elem) != s.end();
}


inline x86_reg strtoreg(string reg)
{
	if (contains(ax, reg))
		return X86_REG_AX;
	else if (contains(bx, reg))
		return X86_REG_BX;
	else if (contains(cx, reg))
		return X86_REG_CX;
	else if (contains(dx, reg))
		return X86_REG_DX;
	else if (contains(si, reg))
		return X86_REG_SI;
	else if (contains(di, reg))
		return X86_REG_DI;
	else if (contains(r9, reg))
		return X86_REG_R9;
	else if (contains(r9, reg))
		return X86_REG_R8;
	return X86_REG_INVALID;	
}


vector<x86_reg> parse_brackets(string operand)
{
	vector<x86_reg> result {0};

	size_t index;
	string creg = "";

	index = operand.find('[');
	if (index == string::npos) //may happen
		return result;
	index += 1;
	
	//we are now positioned within a register
	//we need to read it's name and track it
	for (; operand[index] != ']'; ++index)
	{
		//if this holds the register was read
		if (operand[index] < 'a' || operand[index] > 'z')
		{
			//unless this, because that must have been r8 or r9 register
			if (operand[index] == '8' && operand[index] == '9')
			{
				creg.push_back(operand[index]);
				continue;
			}
				
			//add register to result unless it was invalid
			auto reg = strtoreg(creg);
			if (reg != X86_REG_INVALID)
				result.push_back(reg);

			//reset current register
			creg = "";

			//travel till next register
			while(operand[index] < 'a' || operand[index] > 'z')
			{
				index += 1;
				//in case of end
				if (operand[index] == ']')
					return result;
			}
		}
		else
		{
			creg.push_back(operand[index]);
		}
	}
}


//a function that appends to first set if not in both
template <typename T, typename S>
inline void add_to_first(T elem, set<S> f, set<S> s)
{
	if (!contains(f, elem) && !contains(s, elem))
		f.insert(elem);
}

//a function that given a disassembler will determine the registers used until the ret command or end of disassembly
//first set is registers read, second is registers written
set<x86_reg> registers_used(OneStepDisasm d)
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
				return read;
		}
		else
		{
			auto operands = split(instr.operands, ", ");
			
			//appending registers in brackets
			for (auto i : operands)
			{
				auto t = parse_brackets(i);
				for (auto j : t)
					add_to_first(j, read, written);
			}

			if (contains(good_doubly_operations, instr.mnemonic))
			{
				//check which register it is
				for (auto i : operands)
				{

				}
			}
		}
	}
	return read;
}

CCTypes nikitailDeterminer(OneStepDisasm d)
{
	auto read = registers_used(d);

	cout <<"registers read: ";
	for (auto i : read)
		cout <<i <<' ';
	cout <<endl;


	return none;
}
