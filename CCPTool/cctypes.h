#ifndef CCTYPES_INLCUDED
#define CCTYPES_INLCUDED

//the below values are return types for heuristic functions
//those functions are of type OneStepDisasm -> CCTypes

enum CCTypes
{
	cdecl,
	stdcall,
	msfastcall,
	none
};

#endif
