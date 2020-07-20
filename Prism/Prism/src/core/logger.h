#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Prism {

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
	#define CORE_TRACE(...) ::Prism::PrismLogger::GetEngineLogger()->trace(__VA_ARGS__)
	#define CORE_INFO(...) ::Prism::PrismLogger::GetEngineLogger()->info(__VA_ARGS__)
	#define CORE_WARN(...) ::Prism::PrismLogger::GetEngineLogger()->warn(__VA_ARGS__)
	#define CORE_CRITICAL(...) ::Prism::PrismLogger::GetEngineLogger()->critical(__VA_ARGS__)
	#define CORE_ERROR(...) ::Prism::PrismLogger::GetEngineLogger()->error(__VA_ARGS__)

	#define PRISM_TRACE(...) ::Prism::PrismLogger::GetClientLogger()->trace(__VA_ARGS__)
	#define PRISM_INFO(...) ::Prism::PrismLogger::GetClientLogger()->info(__VA_ARGS__)
	#define PRISM_WARN(...) ::Prism::PrismLogger::GetClientLogger()->warn(__VA_ARGS__)
	#define PRISM_CRITICAL(...) ::Prism::PrismLogger::GetClientLogger()->critical(__VA_ARGS__)
	#define PRISM_ERROR(...) ::Prism::PrismLogger::GetClientLogger()->error(__VA_ARGS__)
#else
	#define CORE_TRACE(...) // Do nothing
	#define CORE_INFO(...) // Do nothing
	#define CORE_WARN(...) // Do nothing
	#define CORE_CRITICAL(...) // Do nothing
	#define CORE_ERROR(...) // Do nothing

	#define PRISM_TRACE(...) // Do nothing
	#define PRISM_INFO(...) // Do nothing
	#define PRISM_WARN(...) // Do nothing
	#define PRISM_CRITICAL(...) // Do nothing
	#define PRISM_ERROR(...) // Do nothing
#endif