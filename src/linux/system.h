#include "os.h"

#ifdef LINUX_OS
#ifndef H_LINUX_SYSTEM
#define H_LINUX_SYSTEM

struct system_state {
	int dummy; // C says no empty structs
};

#endif
#endif
