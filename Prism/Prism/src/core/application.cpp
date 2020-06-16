#include "application.h"

namespace Prism {

	Application::Application() {
        CORE_INFO("Prism Engine initializing startup.");
    };

	Application::~Application() {
        CORE_INFO("Prism Engine preparing to exit.");
    };

	void Application::Run() {
		while (true);
	}

}
