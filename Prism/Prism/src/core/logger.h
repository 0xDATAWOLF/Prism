#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Prism {

	/**
	The application's logger code is here. Uses a form of lazy initialization. Doesn't require
	any outside initialization if the logger isn't fetched. May cause race conditions if it
	isn't initialized before child threads are deployed.
	*/
	class PrismLogger {
		public:
			static void Init();
			static std::shared_ptr<spdlog::logger> & GetClientLogger();
			static std::shared_ptr<spdlog::logger> & GetEngineLogger();

		private:
			static std::shared_ptr<spdlog::logger> _engineLogger;
			static std::shared_ptr<spdlog::logger> _clientLogger;
	};

}

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