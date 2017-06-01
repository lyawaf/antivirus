#include "cctypes.h"
#include "wrapper.h"

//a function that determines the calling convention in a simple way
//it analyzes basic assembler instructions && ret && makes ideas out of that
//if retn has an argument, it's msfastcall or stdcall, otherwise it's cdecl
//if ecx and edx are used before assignment, it's msfastcall
//simple as that

//@@FUNCTION
CCTypes nikitailDeterminer(OneStepDisasm d);
