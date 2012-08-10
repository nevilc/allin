#include "os.h"

#ifdef WINDOWS_OS
#ifndef H_WIN_SYSTEM
#define H_WIN_SYSTEM

struct system_state {
	int dummy; // C says no empty structs
};

#endif
#endif
