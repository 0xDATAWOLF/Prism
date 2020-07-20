#pragma once
#include <memory>

namespace Prism {
	template <class T>
	using Ref = std::shared_ptr<T>;

	template <class T>
	using Scope = std::unique_ptr<T>;
}

// PRISM_ASSERT macro works only on windows
#ifndef _PRISM_ASSERT_MACRO

	// Assertion macro for Windows
	#ifdef PRISM_PLATFORM_WINDOWS
		#define _PRISM_ASSERT_MACRO
		#define PRISM_ASSERT(a,b) if (!(a)) { __debugbreak(); }
	#endif

	// If no other platform defines the macro, define it to do nothing.
	#ifndef _PRISM_ASSERT_MACRO
		#define _PRISM_ASSERT_MACRO
		#define PRISM_ASSERT(a,b)
	#endif

#endif

// Platform windows.
#ifdef PRISM_PLATFORM_WINDOWS
#endif

// Platform OSX.
#ifdef PRISM_PLATFORM_OSX
	// Silence the warning for opengl use on mac.
	// This may be removed for a metal implementation in the future.
	#define GL_SILENCE_DEPRECATION
#endif