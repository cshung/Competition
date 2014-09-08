// Competition.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SPOJ_PALIN.h"
#include "UVa100.h"
#include "UVa272.h"
#include "UVa394.h"

//
// To avoid create a lot of projects/executables for each competition problem,
// each problem answered as a separate file with an entry function
// The entry function is called in main below.
//
// For competition purpose that file is submitted instead
// And the entry function is renamed to main for submission
// Together we will also remove WIN32 specifics
//
int _tmain(int argc, _TCHAR* argv[])
{
	// return SPOJ_PALIN();
	// return UVa100();
	// return UVa272();
	return UVa394();
}

