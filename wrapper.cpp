#include "wrapper.h"
using namespace std;

//TODO: better exceptions
OneStepDisasm::OneStepDisasm(string filename, int mode, uint64_t startaddr)
: _filename(filename)
, _codefile(filename, ios::in|ios::binary|ios::ate) //opening the file in binary mode
{
	if (!_codefile.is_open())
		throw runtime_error("Can't open file");

	//opening disassembler
	if (mode == 32)
		cs_open(CS_ARCH_X86, CS_MODE_32, &_handle);
	else if (mode == 64)
		cs_open(CS_ARCH_X86, CS_MODE_64, &_handle);
	else
		throw runtime_error("Unrecognized mode");
		
	//allocating memory cache
	_insn = cs_malloc(_handle);
	
	_codesize = _codefile.tellg() - startaddr; //a number of bytes from begin to end + 1 is exactly this diffrnce

	_codeBegin = new uint8_t[_codesize];
	_codeCurrent = _codeBegin;

	//positioning at offset startaddr
	_codefile.seekg(startaddr, ios::beg);
	//and reading the file to memory
	//via a bit of casts, because read() expects a *char and capstone expects uint8_t
	auto codeBeginChar = reinterpret_cast<char*>(_codeBegin);
	_codefile.read(codeBeginChar, _codesize);
	_codefile.close();
}
	
OneStepDisasm::~OneStepDisasm()
{
	cs_free(_insn, 1);
	delete[] _codeBegin;
}

cs_insn* OneStepDisasm::next()
{
	bool success = cs_disasm_iter(_handle, &_codeCurrent, &_codesize, &_startaddr, _insn);
	if (!success)
		return NULL;
	return _insn;
}
