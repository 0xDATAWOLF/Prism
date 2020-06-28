#include <core/application.h>
#include <Glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

namespace Prism {

	/* Constructs an application with explicit width, hieght, and title properties as constructor
	arguments. This is forwarded onto Application(WindowProperties &&). */
	Application::Application(uint32_t width, uint32_t height, std::string windowTitle) {
		CORE_INFO("Prism is initializing.");
		CORE_INFO("Creating window W{} H{} titled: {}", width, height, windowTitle);
		_window = Window::Create(WindowProperties{width, height, windowTitle});
		_window->Attach(this);
	};

	Application::~Application() {
		CORE_INFO("Prism is shutting down.");
	};

	void Application::Run() {
		
		while (_running) {
			glClearColor(0.125f, 0.125f, 0.125f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			if (_scene != nullptr) _scene->_pFrameUpdateLayers();
			_window->Update();
		}

	}

	void Application::OnEvent(IEvent* e) {
		//CORE_INFO("Application received an event: {}", e->GetEventName());
		// Detect if the window close event has been called.
		if (e->GetEventType() == EventType::WindowCloseEvent) _running = false;
	}

}