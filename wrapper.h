#ifndef WRAPPER_INCLUDED
#define WRAPPER_INCLUDED

#include <cinttypes>
#include <string>
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
	uint64_t _startaddr;

	int _mode;

	string _filename;
	ifstream _codefile;
	
	shared_ptr<uint8_t> _codeBegin; //code keeper
	const uint8_t* _codeCurrent; //pointer to current instruction
	size_t _codesize;

	
	//so this pretty much copies the capstone struct, but with strings and without bytes representation
	struct instruction
	{
		friend OneStepDisasm;

		//this thing tells if the disassemblation is over && no more instructions can be accessed
		bool empty;

		unsigned int id;
		uint64_t address;
		string mnemonic;
		string operands;

		instruction(const instruction&);

	private:
		instruction(unsigned int cid, uint64_t caddress, const char* cmnemonic, const char* cop_str);
		instruction(bool cempty = true); //only applicable if cempty == true. Throws std::runtime_error
	};

	
public:
	OneStepDisasm(string filename, int mode, uint64_t startaddr); //throws std::runtime_error
	OneStepDisasm(const OneStepDisasm&);
	~OneStepDisasm();

	//a function that disassembles and returns the next instruction
	instruction next();

	//a simple getter
	int getMode();
};

#endif
