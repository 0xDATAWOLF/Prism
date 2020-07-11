#pragma once

#include <core/logger.h>
#ifndef _PRISM_ASSERT_MACRO
	#define _PRISM_ASSERT_MACRO
	#define PRISM_ASSERT(a,b) if (!(a)) { CORE_ERROR("{}",b); __debugbreak(); }
#endif

// Platform windows.
#ifdef PRISM_PLATFORM_WINDOWS
	// No platform dependant macros are defined yet.
#endif

// Platform OSX.
#ifdef PRISM_PLATFORM_OSX
	// Silence the warning for opengl use on mac.
	// This may be removed for a metal implementation in the future.
	#define GL_SILENCE_DEPRECATION
#endif