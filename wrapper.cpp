#include "wrapper.h"
using namespace std;

//TODO: better exceptions
OneStepDisasm::OneStepDisasm(string filename, int mode, uint64_t startaddr)
: _filename(filename)
, _codefile(filename, ios::in|ios::binary|ios::ate) //opening the file in binary mode
{
	if (!_codefile.is_open())
		throw runtime_error("Can't open file");

	_mode = mode;
	
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

	//making a smart pointer point to the new memory location, with custom deleter for arrays
	_codeBegin.reset( new uint8_t[_codesize], charDeleter );
	_codeCurrent = _codeBegin.get();

	//positioning at offset startaddr
	_codefile.seekg(startaddr, ios::beg);
	//and reading the file to memory
	//via a bit of casts, because read() expects a *char and capstone expects uint8_t
	auto codeBeginChar = reinterpret_cast<char*>(_codeCurrent);
	_codefile.read(codeBeginChar, _codesize);
	_codefile.close();
}


OneStepDisasm::OneStepDisasm(OneStepDisasm& r)
: _filename(r._filename)
, _codefile(r._codefile)
, _codeBegin(r._codeBegin)
{
	if (!_codefile.is_open())
		throw runtime_error("Can't open file");

	_mode = r._mode;
	
	//god damn C in big projects
	if (_mode == 32)
		cs_open(CS_ARCH_X86, CS_MODE_32, &_handle);
	else if (_mode == 64)
		cs_open(CS_ARCH_X86, CS_MODE_64, &_handle);
	else
		throw runtime_error("Unrecognized mode");
		
	//allocating memory cache
	_insn = cs_malloc(_handle);

	_codesize = r._codesize;
	_startaddr = r._startaddr;
	_codeCurrent = r._codeCurrent;
}

	
OneStepDisasm::~OneStepDisasm()
{
	cs_free(_insn, 1);
}


cs_insn* OneStepDisasm::next()
{
	bool success = cs_disasm_iter(_handle, &_codeCurrent, &_codesize, &_startaddr, _insn);
	if (!success)
		return NULL;
	return _insn;
}
