#pragma once
#include <functional>
#include <core/core.h>
#include <core/logger.h>
#include <core/events.h>
#include <core/window.h>

namespace Prism {

	/* Application is the core base class of the Prism Engine. It contains all the functionality to interact with
	the engine as well as provide */
	class Application : public IObserver {
	public:

		/* Constructs and initializes the window. */
		Application(uint32_t, uint32_t, std::string);
		Application(WindowProperties &);
		Application(WindowProperties && = WindowProperties());
		virtual ~Application();

		void Run();
		void OnEvent(IEvent*);

	protected:
		std::unique_ptr<Window> _window;

	};

	// This is the user-defined entry point for the Prism Engine. The defined function must return a
	// a heap allocated Prism::Application user-defined derived class.
	Application* CreateApplication();

}
