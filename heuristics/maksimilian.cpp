#include "maksimilian.h"
#include <set>

CCTypes maksimilian(OneStepDisasm& src)
{
	//here we have a set of used_registers ¯\_(ツ)_/¯
	auto used_regs = used_registers(src);
	
	while (true)
	{
		auto instr = src.next();
		if (instr.empty)
			break;
	
		if (contains(instr.groups, CS_GRP_RET))
		{
			//if true it probable stdcall || fastcall
			if (instr.operands != "" && instr.operands != "0")
			{
				
			}
		}
	}
}
