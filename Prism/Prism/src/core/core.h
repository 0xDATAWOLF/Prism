#pragma once

// Global / common includes. Candidates for pre-compiled headers?
// TODO: create pre-compiled headers for includes below.
#include <cstdint>
#include <assert.h>
#include <vector>
#include <array>
#include <memory>
#include <string>
#include <functional>

#include <core/logger.h>

#ifndef _PRISM_ASSERT_MACRO
	#define _PRISM_ASSERT_MACRO
	#define PRISM_ASSERT(a,b) if (a) CORE_ERROR("{}",b); __debugbreak()
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