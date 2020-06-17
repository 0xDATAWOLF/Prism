#pragma once

// Global / common includes. Candidates for pre-compiled headers?
// TODO: create pre-compiled headers for includes below.
#include <cstdint>
#include <assert.h>
#include <vector>
#include <array>
#include <memory>

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
    #define GL_SILENCE_DEPRECATION
	#ifdef PRISM_BUILD_DLL
		#define PRISM_API
	#else
		#define PRISM_API
	#endif 
#endif

#ifdef PRISM_DEBUG
    #define CORE_TRACE(...) Prism::PrismLogger::GetEngineLogger()->trace(__VA_ARGS__)
    #define CORE_INFO(...) Prism::PrismLogger::GetEngineLogger()->info(__VA_ARGS__)
    #define CORE_WARN(...) Prism::PrismLogger::GetEngineLogger()->warn(__VA_ARGS__)
    #define CORE_CRITICAL(...) Prism::PrismLogger::GetEngineLogger()->critical(__VA_ARGS__)
    #define CORE_ERROR(...) Prism::PrismLogger::GetEngineLogger()->error(__VA_ARGS__)

    #define PRISM_TRACE(...) Prism::PrismLogger::GetClientLogger()->trace(__VA_ARGS__)
    #define PRISM_INFO(...) Prism::PrismLogger::GetClientLogger()->info(__VA_ARGS__)
    #define PRISM_WARN(...) Prism::PrismLogger::GetClientLogger()->warn(__VA_ARGS__)
    #define PRISM_CRITICAL(...) Prism::PrismLogger::GetClientLogger()->critical(__VA_ARGS__)
    #define PRISM_ERROR(...) Prism::PrismLogger::GetClientLogger()->error(__VA_ARGS__)
#endif
