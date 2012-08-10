#include "os.h"

#ifdef WINDOWS_OS

#include "error.h"

#include <stdio.h>

#include <Psapi.h>

void windows_error(const LPTSTR function_name) {
	// Retrieve the system error message for the last-error code
	
	LPVOID msg_buffer;
	DWORD error_code = GetLastError();
		
	if (error_code == 0) {
		// No error available
		return;
	}
	
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		error_code,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR) &msg_buffer,
		0, NULL);
	
	fprintf(stderr, "Error in function %s(): %s\n", function_name, (LPTSTR) &msg_buffer);
	
	LocalFree(msg_buffer);
	//ExitProcess(dw);
}

#endif//WINDOWS_OS
