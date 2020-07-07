#include <core/logger.h>

namespace Prism {

	inline std::shared_ptr<spdlog::logger> PrismLogger::_clientLogger;
	inline std::shared_ptr<spdlog::logger> PrismLogger::_engineLogger;

	void PrismLogger::Init() {
		spdlog::set_pattern("%^[%T.%e][%n][%l][thread %t]%$ : %v"); // set pattern
		_engineLogger = spdlog::stdout_color_mt("Prism");
		_clientLogger = spdlog::stdout_color_mt("Application");
		_engineLogger->set_level(spdlog::level::trace);
		_clientLogger->set_level(spdlog::level::trace);
	}

	std::shared_ptr<spdlog::logger>& PrismLogger::GetClientLogger() {
		return _clientLogger;
	};

	std::shared_ptr<spdlog::logger>& PrismLogger::GetEngineLogger() {
		return _engineLogger;
	}

}
