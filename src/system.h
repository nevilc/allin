#ifndef H_SYSTEM
#define H_SYSTEM

#include "os.h"

struct system_state;

EXPORT void system_sleep(struct system_state* state, int ms);

#include "win/system.h"
#include "linux/system.h"

#endif//H_SYSTEM
