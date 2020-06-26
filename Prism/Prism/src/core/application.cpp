#include <core/application.h>
#include <Glad/glad.h>
#include <GLFW/glfw3.h>

namespace Prism {

	/* Constructs an application with a WindowProperties object. This is the default constructor. */
	Application::Application(WindowProperties && winprops) {
		CORE_INFO("Prism is initializing.");
		CORE_INFO("Creating window W{} H{} titled: {}", winprops.width, winprops.height, winprops.title);
		_window = Window::Create(winprops); // Platform detection is done in this static method.
		_window->Attach(this);

	}

	/* Constructs an application with a WindowProperties object. This is forwarded onto
	Application(WindowProperties &&) using move semantics. */
	Application::Application(WindowProperties& winprops) :
		Application(std::move(winprops)) {};

	/* Constructs an application with explicit width, hieght, and title properties as constructor
	arguments. This is forwarded onto Application(WindowProperties &&). */
	Application::Application(uint32_t width, uint32_t height, std::string windowTitle) :
		Application(WindowProperties(width, height, windowTitle)) {};

	Application::~Application() {
		CORE_INFO("Prism is shutting down.");
	};

	void Application::Run() {
		
		// This is platform dependant code, this needs to be revised.
		// Decouple from GLFW is advisable.
		while (_running) {
			glClearColor(0.125f, 0.125f, 0.125f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			_window->Update();
		}

	}

	void Application::OnEvent(IEvent* e) {
		//CORE_INFO("Application received an event: {}", e->GetEventName());
		// Detect if the window close event has been called.
		if (e->GetEventType() == EventType::WindowCloseEvent) _running = false;
	}

}