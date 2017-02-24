#ifndef WRAPPER_INCLUDED
#define WRAPPER_INCLUDED

#include <cinttypes>
#include <string>
#include <set>
#include <iostream>
#include <fstream>
#include <memory>
using namespace std;

#include <capstone/capstone.h>

//deleter used for arrays of text
auto uint8Deleter = [](uint8_t* pointer) -> void { delete[] pointer; };


class OneStepDisasm
{
private:
	csh _handle;
	cs_insn *_insn;
	uint64_t _startaddr; //startaddr for physical address
	uint64_t _v_addr; //and v_addr for virtual
	size_t _lifetime; //max value of jumps to be explored

	int _mode;

	string _filename;
	ifstream _codefile;
	
	shared_ptr<uint8_t> _code_begin; //code keeper
	const uint8_t* _code_current; //pointer to current instruction
	size_t _codesize;

	
	//so this pretty much copies the capstone struct, but with strings and without bytes representation
	struct instruction
	{
		friend OneStepDisasm;

		//this thing tells if the disassemblation is over && no more instructions can be accessed
		const bool empty;

		const unsigned int id;
		const uint64_t address;
		const string mnemonic;
		const string operands;

		//details (not all)
		const set<uint8_t> groups; //the fuck, this should be an enum. Why-why those ceeshniki

		instruction(const instruction&);
		instruction();

	private:
		instruction(unsigned int cid, uint64_t caddress, const char* cmnemonic, const char* cop_str, cs_detail* details);
		instruction(bool cempty = true); //only applicable if cempty == true. Throws std::runtime_error
	};

	
public:
	OneStepDisasm(string filename, int mode, uint64_t startaddr, uint64_t _v_addr); //throws std::runtime_error
	OneStepDisasm(const OneStepDisasm&);
	~OneStepDisasm();

	//a function that disassembles and returns the next instruction
	instruction next();

	//a simple getter
	int get_mode();

	//a function that clones on given virtual address
	OneStepDisasm clone_at(const uint64_t &addr);
};

#endif
