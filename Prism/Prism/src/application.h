#pragma once
#include "core/window.h"
#include "core/layerstack.h"
#include "imgui/imgui_layer.h"

int main(int argc, char** argv); // fwd dec main

namespace Prism {

	class Application : public IObserver {

	public:
		friend int ::main(int argc, char** argv);

		Application(uint32_t, uint32_t, std::string);
		virtual ~Application();
		
		template <class L> void PushLayer();
		template <class L> void PushOverlay();
		void PopLayer(Layer*);
		void PopOverlay(Layer*);

		inline void* GetNativeWindow() { return _window->GetWindowPtr(); }
		inline uint32_t GetWindowWidth() { return _window->GetWidth(); }
		inline uint32_t GetWindowHeight() { return _window->GetHeight(); }

		inline static Application& Get() { return *_singletonInstance; };

	private:
		void OnEvent(IEvent*);
		bool OnWindowClose(WindowCloseEvent*);
		bool OnWindowResize(WindowResizeEvent*);

		void Run();

		Scope<LayerStack> _layerStack;
		Scope<ImGUILayer> _imguiLayer;
		Scope<Window> _window;
		Timestep _timestep;

		bool _running = true;

	private:
		static Application* _singletonInstance;

	};

	template <class L>
	inline void Application::PushLayer() {
		_layerStack->Push<L>(); //fwd
	}

	template <class L>
	inline void Application::PushOverlay() {
		_layerStack->PushOverlay<L>(); // fwd
	}

}

namespace Prism {

	Application* CreateApplication(); // dec

}