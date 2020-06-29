#include <core/application.h>
#include <Glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

namespace Prism {

	Application* Application::_singletonInstance = nullptr;

	Application::Application(uint32_t width, uint32_t height, std::string windowTitle) {
		if (_singletonInstance == nullptr) _singletonInstance = this;
		else throw "Only one instance of Application is allowed.";

		CORE_INFO("Creating window W{} H{} titled: {}", width, height, windowTitle);
		_window = Window::Create(WindowProperties{width, height, windowTitle});
		_window->Attach(this);

		_layerStack = std::make_unique<LayerStack>(LayerStack());
	};

	Application::~Application() {
		CORE_INFO("Prism is shutting down.");
	};

	void Application::PopLayer(Layer* layer) {
		_layerStack->PopLayer(layer); // fwd
	}

	void Application::Run() {

		while (_running) {
			glClearColor(0.125f, 0.125f, 0.125f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			_layerStack->UpdateLayers();
			_window->Update();
		}

	}

	void Application::OnEvent(IEvent* e) {
		//CORE_INFO("Application received an event: {}", e->GetEventName());
		if (e->GetEventType() == EventType::WindowCloseEvent) _running = false;
	}

}