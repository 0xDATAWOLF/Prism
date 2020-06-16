#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "core.h"

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
