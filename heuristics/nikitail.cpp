#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <cassert>

#include "nikitail.h"

using std::cout;
using std::endl;
using std::hex;
using std::set;
using std::vector;
using std::stringstream;
using std::getline;



constexpr bool DEBUG = false;


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
set<string> bp {
	"rbp", "ebp", "bp"
};
set<string> sp {
	"rbp", "esp", "sp"
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


//as it's better to operate with register types && not strings,
//we use this function to convert
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
	else if (contains(bp, reg))
		return X86_REG_BP;
	else if (contains(sp, reg))
		return X86_REG_SP;
	else if (contains(r9, reg))
		return X86_REG_R9;
	else if (contains(r9, reg))
		return X86_REG_R8;
	else
		return X86_REG_INVALID;	
}


//finds out which registers were used in [] in operand
set<x86_reg> parse_brackets(const string& operand)
{
	set<x86_reg> result;

	size_t index;
	string creg = "";

	index = operand.find('[');
	if (index == string::npos) //may happen
		return result;
	index += 1;
	
	//we are now positioned within a register
	//we need to read it's name and track it
	for (; operand[index-1] != ']'; ++index)
	{
		//if this holds the register was read
		if (operand[index] < 'a' || operand[index] > 'z')
		{
			//unless this, because that must have been r8 or r9 register
			if (operand[index] == '8' || operand[index] == '9')
			{
				creg.push_back(operand[index]);
				continue;
			}
				
			//add register to result unless it was invalid
			auto reg = strtoreg(creg);
			if (DEBUG)
				cout << "found in []: " <<creg <<endl;
			if (reg != X86_REG_INVALID)
				result.insert(reg);
			else if (DEBUG)
				cout <<"it was invalid? " <<creg <<endl;

			//reset current register
			creg = "";

			//travel till next register
			while(operand[index] < 'a' || operand[index] > 'z')
			{
				index += 1;
				//in case of end
				if (operand[index] == ']' || operand[index] == '\0')
					return result;
			}
			index -= 1;
		}
		else
		{
			creg.push_back(operand[index]);
		}
	}
	return result;
}


//finds out which registers were used in an operand
set<x86_reg> parse_operand(const string& operand)
{
	if (operand.find('[') != string::npos)
	{
		return parse_brackets(operand);
	}
	auto r = strtoreg(operand);
	if (r == X86_REG_INVALID)
	{
		return set<x86_reg>();
	}
	return set<x86_reg> {r};
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
		{
			if (DEBUG)
			{
				cout << "stopping on empty instruction\n";
			}
			break;
		}

		if (DEBUG)
		{
			cout << "0x" <<hex << instr.address <<"\t\t" <<instr.mnemonic <<"\t" <<instr.operands <<endl;
		}

		//for now i choose to ignore jump && call instructions
		if (contains(instr.groups, CS_GRP_JUMP))
		{
			auto dest = parse_operand(instr.operands);
			if (DEBUG)
			{
				cout << "found a jump command: ";
				if (dest.empty())
				{
					cout << "offset " << instr.operands <<endl;
				}
				else
				{
					cout << "expression " << instr.operands <<endl;
				}
			}
		}
		else if (contains(instr.groups, CS_GRP_CALL))
		{
			auto dest = parse_operand(instr.operands);
			if (DEBUG)
			{
				cout << "found a call command: ";
				if (dest.empty())
				{
					cout << "offset " << instr.operands <<endl;
				}
				else
				{
					cout << "expression " << instr.operands <<endl;
				}
			}
		}
		else if (contains(instr.groups, CS_GRP_RET))
		{
			if (DEBUG)
			{
				cout << "found a return command\n";
			}
			if (!DEBUG)
			{
				return read;
			}
		}
		else
		{
			auto operands = split(instr.operands, ", ");
			
			if (contains(good_doubly_operations, instr.mnemonic))
			{
				assert(operands.size() == 2);
				//add every parsed register as read
				for (auto i : operands)
				{
					auto t = parse_operand(i);
					read.insert(t.begin(), t.end());
				}
			}
			else if (contains(good_rightly_operations, instr.mnemonic))
			{
				assert(operands.size() == 2);
				//add only right-hand parsed operand as read
				auto t = parse_operand(operands[1]);
				read.insert(t.begin(), t.end());
				//also if there were brackets involved, they were also read, add them
				t = parse_brackets(operands[0]);
				read.insert(t.begin(), t.end());
			}
		}
	}
	return read;
}

CCTypes nikitailDeterminer(OneStepDisasm d)
{
	auto read = registers_used(d);

//	if (DEBUG)
//	{
		cout <<"registers read: ";
		for (auto i : read)
			cout <<i <<' ';
		cout <<endl;
//	}


	return none;
}
