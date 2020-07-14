// Entry point for the application
#include "core/logger.h"


/**
 Performs platform independent initialization steps.
 */
void _init() {
	Prism::PrismLogger::Init();
}

#ifdef PRISM_PLATFORM_WINDOWS
	extern Prism::Application* Prism::CreateApplication();
	int main(int argc, char ** argv) {
		_init();
		auto _app = Prism::CreateApplication();
		_app->Run();
		delete _app;
	}
#endif

#ifdef PRISM_PLATFORM_OSX
	extern Prism::Application * Prism::CreateApplication();
	int main(int argc, char ** argv) {
		_init();
		auto _app = Prism::CreateApplication();
		_app->Run();
		delete _app;
		return 0;
	}
#endif
