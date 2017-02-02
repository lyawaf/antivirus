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
	
public:
	OneStepDisasm(string filename, int mode, uint64_t startaddr); //throws std::runtime_error
	OneStepDisasm(OneStepDisasm&);
	~OneStepDisasm();
	cs_insn* next();
};

#endif
