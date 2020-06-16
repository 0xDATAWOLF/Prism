#pragma once

// Global / common includes. Candidates for pre-compiled headers?
// TODO: create pre-compiled headers for includes below.
#include <cstdint>
#include <assert.h>
#include <vector>
#include <array>

// Platform windows.
#ifdef PRISM_PLATFORM_WINDOWS
	#ifdef PRISM_BUILD_DLL
		#define PRISM_API __declspec(dllexport)
	#else
		#define PRISM_API __declspec(dllimport)
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
