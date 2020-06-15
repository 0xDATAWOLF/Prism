#pragma once

#ifdef PRISM_PLATFORM_WINDOWS

extern Prism::Application* Prism::CreateApplication();
int main(int argc, char ** argv) {
	//Prism::Logger::Init();
	auto _app = Prism::CreateApplication();
	_app->Run();
	delete _app;
}

#endif

#ifdef PRISM_PLATFORM_OSX

extern Prism::Application * Prism::CreateApplication();
int main(int argc, char ** argv) {
    auto _app = Prism::CreateApplication();
    _app->Run();
    delete _app;
}

#endif