#include <functional>
#include "application.h"
#include "renderer/renderer.h"

namespace Prism {

	Application* Application::_singletonInstance = nullptr;

	Application::Application(uint32_t width, uint32_t height, std::string windowTitle) {
		if (_singletonInstance == nullptr) _singletonInstance = this;
		else throw "Only one instance of Application is allowed.";

		_window = Window::Create(width, height, windowTitle);
		_window->Attach(this);

		Renderer::Init();
		Renderer2D::Init();

		_layerStack = std::make_unique<LayerStack>();
		_imguiLayer = std::make_unique<ImGUILayer>();
		_layerStack->PushOverlayUnmanaged(_imguiLayer.get());

		_window->SetVsync(true);

	};

	Application::~Application() {};

	void Application::PopLayer(Layer* layer) {
		_layerStack->Pop(layer); // fwd
	}

    void Application::PopOverlay(Layer* layer) {
		_layerStack->PopOverlay(layer); // fwd
	}

	void Application::Run() {

		while (_running) {

			for (auto& layer : *_layerStack)
				layer->Update(_timestep);

			_imguiLayer->Begin();
			for (auto layer : *_layerStack)
				layer->ImGuiRender();
			_imguiLayer->End();

			_window->Update();
			
			Input::SwapStates();
			Input::ValidateHoldStates();
			_timestep.Update();

		}

	}

	void Application::OnEvent(IEvent* e) {

		IDispatcher dispatcher(e);
		dispatcher.Forward<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
		dispatcher.Forward<WindowResizeEvent>(std::bind(&Application::OnWindowResize, this, std::placeholders::_1));

		for (auto layer : *_layerStack) {
			if (!e->IsHandled()) layer->OnEvent(e); // fwd to layers
			else break;
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