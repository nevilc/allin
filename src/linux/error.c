#include "os.h"

#ifdef LINUX_OS

#include "error.h"

#include <stdio.h>

#define BUFFER_SIZE 1024
	
void linux_x_error(Display* display, const char* function_name, int error_code) {	
	char error_text[BUFFER_SIZE];
	XGetErrorText(display, error_code, error_text, BUFFER_SIZE);
	fprintf(stderr, "Error in function %s(): %s\n", function_name, error_text);
	
	return;
}
	
#undef BUFFER_SIZE

#endif//LINUX_OS
