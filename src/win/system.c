#include "os.h"

#ifdef WINDOWS_OS

#include "../system.h"

EXPORT void system_sleep(struct system_state* state, int ms) {
	Sleep(ms);
}

#endif//WINDOWS_OS
