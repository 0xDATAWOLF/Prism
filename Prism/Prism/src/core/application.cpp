#include <core/application.h>
#include <core/input.h>
#include <imgui.h>

#include <glad/glad.h>

namespace Prism {

	Application* Application::_singletonInstance = nullptr;

	Application::Application(uint32_t width, uint32_t height, std::string windowTitle) {
		if (_singletonInstance == nullptr) _singletonInstance = this;
		else throw "Only one instance of Application is allowed.";

		CORE_INFO("Creating window W{} H{} titled: {}", width, height, windowTitle);
		_window = Window::Create(WindowProperties{width, height, windowTitle});
		_window->Attach(this);

		Input::_singletonInstance = new Input();

		_layerStack = std::make_unique<LayerStack>(LayerStack());
	};

	Application::~Application() {
		CORE_INFO("Prism is shutting down.");
		delete Input::_singletonInstance;
	};

	void Application::PopLayer(Layer* layer) {
		_layerStack->Pop(layer); // fwd
	}

    void Application::PopOverlay(Layer* layer) {
		_layerStack->PopOverlay(layer); // fwd
	}

	void Application::Run() {

		while (_running) {

			// Temporary
			glClearColor(0.125f, 0.125f, 0.125f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			for (auto layer : *_layerStack) layer->Update();
			_window->Update();
		}

	}

	void Application::OnEvent(IEvent* e) {
		if (e->GetEventType() != EventType::MouseMoveEvent) CORE_INFO("Event received: {}", e->GetEventName());

		IDispatcher dispatcher(e);
		dispatcher.Forward<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
		dispatcher.Forward<WindowResizeEvent>(std::bind(&Application::OnWindowResize, this, std::placeholders::_1));

		for (auto layer : *_layerStack) {
			if (!e->IsHandled()) layer->OnEvent(e); // fwd to layers
		}

	}

	bool Application::OnWindowClose(WindowCloseEvent* e) {
		_running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent* e) {
		_window->SetHeight(e->GetHeight());
		_window->SetWidth(e->GetWidth());
		return false;
	}

}