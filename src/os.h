#ifndef H_OS
#define H_OS

// Determine which operating system is being compiled for

#define EXPORT 

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__)
	#define WINDOWS_OS
    #define WINDOWS32_OS
    // Require Windows 2000+
    //#define _WIN32_WINNT 0x0500
    // Require Windows Vista+
    //#define _WIN32_WINNT 0x0600
	
	
	#undef EXPORT
	#ifdef LIB
		#define EXPORT __declspec(dllexport)
	#else
		#define EXPORT __declspec(dllimport)
	#endif
	
#elif defined(WIN64) || defined(_WIN64)
	#define WINDOWS_OS
	#define WINDOWS64_OS
	
	#ifdef DLL
		#define EXPORT __declspec(dllexport)
	#else
		#define EXPORT __declspec(dllimport)
	#endif
	
#elif defined(__linux__) || defined(__linux) || defined(linux)
    #define LINUX_OS
#elif defined(__unix__) || defined(__unix) || defined(_POSIX_VERSION) || defined(_POSIX2_VERSION) || defined(_XOPEN_VERSION)
	#define UNIX_OS
#elif defined(macintosh) || defined(Macintosh)
	#define APPLE_OS
	#define APPLE9_OS
#elif defined(__APPLE__) || defined(__MACH__) || defined(__OSX__)
	#define APPLE_OS
	#define APPLEX_OS
#else
	#error "Unsupported operating system"
#endif

#ifdef WINDOWS_OS
	// Windows will define min and max macros that mess everything up if we let it
	#define NOMINMAX
	#define WIN32_LEAN_AND_MEAN
	
    #include <Windows.h>
#endif//WINDOWS_OS

#ifdef LINUX_OS
	// Require Xorg
	#include <X11/Xlib.h>
#endif//LINUX_OS

#endif//H_OS
