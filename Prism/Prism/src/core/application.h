#pragma once
#include <core/core.h>
#include <core/logger.h>
#include <core/events.h>
#include <core/window.h>
#include <core/scene.h>

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

		/* Sets a scene using the template argument. */
		template<class DerivedSceneClass> inline void SetScene() { _scene = std::make_shared<DerivedSceneClass>(DerivedSceneClass()); };

		/* Executes the application runtime, performed automatically. Do not call this method. */
		void Run();

	private:
		void OnEvent(IEvent*);
		std::shared_ptr<Scene> _scene;

	private:
		std::unique_ptr<Window> _window;
		bool _running = true;

	};

	// This is the user-defined entry point for the Prism Engine. The defined function must return a
	// a heap allocated Prism::Application user-defined derived class.
	Application* CreateApplication();

}