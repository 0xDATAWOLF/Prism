#pragma once

#define PRISM_PLATFORM_OSX
#define PRISM_BUILD_DLL

// Platform windows.
#ifdef PRISM_PLATFORM_WINDOWS
	#ifdef PRISM_BUILD_DLL
		#define PRISM_API __declspec(dllexport)
	#else
		#define PRISM_API _declspec(dllimport)
	#endif 
#endif

// Platform OSX. No declspec required, empty token.
#ifdef PRISM_PLATFORM_OSX
	#ifdef PRISM_BUILD_DLL
		#define PRISM_API
	#else
		#define PRISM_API
	#endif 
#endif