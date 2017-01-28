#include <cstdio>

#include "wrapper.h"
using namespace std;

int main(int argc, char** argv)
{
	string filename = "bin.bin";
	OneStepDisasm d(filename, 64, 1);
	
	for (auto ins = d.next(); ins != NULL; ins = d.next())
		printf("0x%" PRIx64 ":\t%s\t\t%s\n", ins[0].address, ins[0].mnemonic, ins[0].op_str);
	
	return 0;
}
