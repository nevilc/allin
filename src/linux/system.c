#include "os.h"

#ifdef LINUX_OS

#include "../system.h"

#include <errno.h>

EXPORT void system_sleep(struct system_state* state, int ms) {
	struct timespec timein;
	struct timespec timeout;

	timein.tv_sec = ms / 1000;
	timein.tv_nsec = (ms % 1000) * 1000000;
	
	if (nanosleep(&timein, &timeout) == -1) {
		if (errno == EFAULT || errno == EINVAL) {
			// ERROR
		} else if (errno == EINTR) {
			system_sleep(state, timeout.tv_sec * 1000 + timeout.tv_nsec / 1000000);
		}
	}
}

#endif//LINUX_OS
