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
//constexpr bool DEBUG = true;


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


set<string> operations_rr {
	"cmp"
};
set<string> operations_wr {
	"mov", "movb", "lea"
};
set<string> operations_br {
	"add", "sub", "dec", "xor", "and", "or", "shl", "shr"
};
set<string> operations_w {
	"pop"
};
set<string> operations_wa {
	"mul", "div"
};
set<string> operations_wc {
	"mul", "div"
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
	"rsp", "esp", "sp"
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
inline bool contains(const set<T>& s, const P& elem)
{
	return s.find(elem) != s.end();
}
//determines wether some string in set is a superstring of seekee
bool contains_as_substring(const set<string>& s, const string& elem)
{
	for (auto i : s)
	{
		if (i.find(elem) != string::npos)
			return true;
	}
	return false;
}


//as it's better to operate with register types and not strings,
//we use this function to convert
inline x86_reg strtoreg(const string& reg)
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
//and back
string regtostr(const x86_reg& reg)
{
	switch (reg)
	{
		case X86_REG_AX:
			return "AX";
			break;
		case X86_REG_BX:
			return "BX";
			break;
		case X86_REG_CX:
			return "CX";
			break;
		case X86_REG_DX:
			return "DX";
			break;
		case X86_REG_SI:
			return "SI";
			break;
		case X86_REG_DI:
			return "DI";
			break;
		case X86_REG_BP:
			return "BP";
			break;
		case X86_REG_SP:
			return "SP";
			break;
		case X86_REG_R9:
			return "R9";
			break;
		case X86_REG_R8:
			return "R8";
			break;
		default:
			return "undefined";
	}
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
				cout << "found in []: " << creg << endl;
			if (reg != X86_REG_INVALID)
				result.insert(reg);
			else if (DEBUG)
				cout << "it was invalid? " << creg << endl;

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
set<x86_reg> parse_operand(const string& operand, bool lookup_brackets = true)
{
	if (lookup_brackets && operand.find('[') != string::npos)
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
inline void add_to_first(const T& elem, set<S>& f, const set<S>& s)
{
	if (!contains(f, elem) && !contains(s, elem))
		f.insert(elem);
}
//same but adds a set of elements
template <typename T, typename S>
inline void add_to_first(const set<T>& inp, set<S>& f, const set<S>& s)
{
	for (auto i : inp)
		add_to_first(i, f, s);
}


//a function that given a disassembler will determine the registers used until the ret command or end of disassembly
//first set is registers read, second is registers written
pair< set<x86_reg>, set<x86_reg> > registers_used(OneStepDisasm& d)
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
			cout << "0x" << hex << instr.address << "\t\t" << instr.mnemonic << "\t" << instr.operands << endl;
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
					cout << "offset " << instr.operands << endl;
				}
				else
				{
					cout << "expression " << instr.operands << endl;
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
					cout << "offset " << instr.operands << endl;
				}
				else
				{
					cout << "expression " << instr.operands << endl;
				}
			}
		}
		else if (contains(instr.groups, CS_GRP_RET))
		{
			if (DEBUG)
			{
				cout << "found a return command with argument: ";
				if (instr.operands.empty())
					cout << "none\n";
				else
					cout << stoi(instr.operands, nullptr, 16) << endl;
			}
			return make_pair(read, written);
		}
		else
		{
			auto operands = split(instr.operands, ", ");
			
			if (contains_as_substring(operations_wr, instr.mnemonic))
			{
				assert(operands.size() == 2);
				//a recurring pattern: check firest operand for all read
				auto t = parse_operand(operands[1], true);
				if (DEBUG)
				{
					cout << "read: ";
					for (auto reg : t)
						cout << regtostr(reg) << ' ';
					if (t.empty())
						cout << "none";
					cout << endl;
				}
				add_to_first(t, read, written);
				//remember that brackets were read
				t = parse_brackets(operands[0]);
				if (DEBUG)
				{
					cout << "read: ";
					for (auto reg : t)
						cout << regtostr(reg) << ' ';
					if (t.empty())
						cout << "none";
					cout << endl;
				}
				add_to_first(t, read, written);
				//and second for read and written
				t = parse_operand(operands[0], false);
				if (DEBUG)
				{
					cout << "written: ";
					for (auto reg : t)
						cout << regtostr(reg) << ' ';
					if (t.empty())
						cout << "none";
					cout << endl;
				}
				written.insert(t.begin(), t.end());
			}
			else if (contains_as_substring(operations_rr, instr.mnemonic))
			{
				assert(operands.size() == 2);
				
				for (auto op : operands)
				{
					auto t = parse_operand(op, true);
					if (DEBUG)
					{
						cout << "read: ";
						for (auto reg : t)
							cout << regtostr(reg) << ' ';
						if (t.empty())
							cout << "none";
						cout << endl;
					}
					add_to_first(t, read, written);
				}
			}
			else if (contains_as_substring(operations_br, instr.mnemonic))
			{
				assert(operands.size() == 2);

				auto t = parse_operand(operands[1], true);
				if (DEBUG)
				{
					cout << "read: ";
					for (auto reg : t)
						cout << regtostr(reg) << ' ';
					if (t.empty())
						cout << "none";
					cout << endl;
				}
				add_to_first(t, read, written);
				//first parse brackets as read
				t = parse_brackets(operands[0]);
				if (DEBUG)
				{
					cout << "read: ";
					for (auto reg : t)
						cout << regtostr(reg) << ' ';
					if (t.empty())
						cout << "none";
					cout << endl;
				}
				add_to_first(t, read, written);
				//here we first set them as read, then as written
				t = parse_operand(operands[0], false);
				if (DEBUG)
				{
					cout << "read/written: ";
					for (auto reg : t)
						cout << regtostr(reg) << ' ';
					if (t.empty())
						cout << "none";
					cout << endl;
				}
				add_to_first(t, read, written);
				written.insert(t.begin(), t.end());
			}
			else if (contains_as_substring(operations_w, instr.mnemonic))
			{
				assert(operands.size() == 1);
				
				auto t = parse_brackets(operands[0]);
				if (DEBUG)
				{
					cout << "read: ";
					for (auto reg : t)
						cout << regtostr(reg) << ' ';
					if (t.empty())
						cout << "none";
					cout << endl;
				}
				add_to_first(t, read, written);

				t = parse_operand(operands[0], false);
				if (DEBUG)
				{
					cout << "written: ";
					for (auto reg : t)
						cout << regtostr(reg) << ' ';
					if (t.empty())
						cout << "none";
					cout << endl;
				}
				written.insert(t.begin(), t.end());
			}
			else if (contains_as_substring(operations_wa, instr.mnemonic))
			{
				assert(operands.size() == 1);
				//similar to just w
				auto t = parse_brackets(operands[0]);
				if (DEBUG)
				{
					cout << "read: ";
					for (auto reg : t)
						cout << regtostr(reg) << ' ';
					if (t.empty())
						cout << "none";
					cout << endl;
				}
				add_to_first(t, read, written);

				t = parse_operand(operands[0], false);
				if (DEBUG)
				{
					cout << "written: ";
					for (auto reg : t)
						cout << regtostr(reg) << ' ';
					if (t.empty())
						cout << "none";
					cout << endl;
				}
				written.insert(t.begin(), t.end());
				//but also add ax as read and written
				add_to_first(X86_REG_AX, read, written);
				written.insert(X86_REG_AX);
			}
			else if (contains_as_substring(operations_wc, instr.mnemonic))
			{
				assert(operands.size() == 1);
				//same as wa, but with cx
				auto t = parse_brackets(operands[0]);
				if (DEBUG)
				{
					cout << "read: ";
					for (auto reg : t)
						cout << regtostr(reg) << ' ';
					if (t.empty())
						cout << "none";
					cout << endl;
				}
				add_to_first(t, read, written);

				t = parse_operand(operands[0], false);
				if (DEBUG)
				{
					cout << "written: ";
					for (auto reg : t)
						cout << regtostr(reg) << ' ';
					if (t.empty())
						cout << "none";
					cout << endl;
				}
				written.insert(t.begin(), t.end());
				//but also add ax cs read and written
				add_to_first(X86_REG_CX, read, written);
				written.insert(X86_REG_CX);
			}
			else
			{
				//no need to do anything, we don't know what this is
			}
		}
	}
	return make_pair(read, written);
}

CCTypes nikitailDeterminer(OneStepDisasm d)
{
	auto t = registers_used(d);
	auto read = t.first;
	auto written = t.second;

	if (DEBUG)
	{
		cout << "registers read: ";
		for (auto i : read)
			cout << regtostr(i) << ' ';
		if (read.empty())
			cout << "none";
		cout << endl;
		cout << "registers written: ";
		for (auto i : written)
			cout << regtostr(i) << ' ';
		if (written.empty())
			cout << "none";
		cout << endl;

		cout << "ended with:\n";
		auto instr = d.current();
		cout << "0x" << hex << instr.address << "\t\t" << instr.mnemonic << "\t" << instr.operands << endl;
	}

//	if (d.get_mode() == 64)
//		throw std::runtime_error("64bit mode not implemented");

	set<x86_reg> fastcall_regs {X86_REG_AX, X86_REG_DX, X86_REG_CX, X86_REG_R8, X86_REG_R9, X86_REG_DI, X86_REG_SI};

	for (auto i : fastcall_regs)
	{
		if (contains(read, i))
		{
			return msfastcall;
		}
	}
	if (d.current().operands.empty())
	{
		return cdecl;
	}
	else
	{
		return stdcall;
	}

	return none;
}
