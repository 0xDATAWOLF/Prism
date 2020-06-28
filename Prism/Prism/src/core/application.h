#pragma once
#include <core/core.h>
#include <core/logger.h>
#include <core/events.h>
#include <core/window.h>
#include <core/scene.h>

int main(int argc, char** argv); // Forward dec main.

namespace Prism {

	/* Application is the core base class of the Prism Engine. It contains all the
	functionality to interact with the engine as well as provide */
	class Application : public IObserver {

	public:

		friend int ::main(int argc, char** argv);

		/* Constructs and initializes the window. */
		Application(uint32_t, uint32_t, std::string);
		virtual ~Application();

		/* SetScene replaces the current scene with a new scene. */
		template<class S> void SetScene() {
			_scene = std::make_shared<S>(S());
		};

		/* Returns a pointer to the currently active scene. */
		template<class S> S* GetScene() {
			return dynamic_cast<S*>(_scene.get());
		}

	private:
		void OnEvent(IEvent*);
		std::shared_ptr<Scene> _scene;

		std::unique_ptr<Window> _window;
		bool _running = true;

		/* Executes the application runtime, performed automatically. Do NOT call this method. */
		void Run();

	private:
		static Application* _singletonInstance;

	};

	// This is the user-defined entry point for the Prism Engine. The defined function must return a
	// a heap allocated Prism::Application user-defined derived class.
	Application* CreateApplication();

}