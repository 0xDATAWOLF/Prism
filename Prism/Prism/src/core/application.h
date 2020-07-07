#pragma once
#include <core/core.h>
#include <core/logger.h>
#include <core/events.h>
#include <core/window.h>
#include <core/input.h>
#include <core/layerstack.h>
#include <core/imgui/imgui_layer.h>

#include <core/renderer/shader.h>
#include <core/renderer/buffer.h>

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

		std::unique_ptr<LayerStack> _layerStack;
		std::unique_ptr<ImGUILayer> _imguiLayer;
		std::unique_ptr<Window> _window;

		bool _running = true;

	private:
		static Application* _singletonInstance;

	// ------------------------------------------------------------------ \\
	// --- Temporary ---------------------------------------------------- //
	// ------------------------------------------------------------------ \\
	private:
		uint32_t _vao;
		std::unique_ptr<Shader> _basicShader;
		std::unique_ptr<VertexBuffer> _vertexBuffer;
		std::unique_ptr<VertexBuffer> _colorBuffer;
		std::unique_ptr<IndexBuffer> _indexBuffer;
	// ------------------------------------------------------------------ //
	// --- End ---------------------------------------------------------- \\
	// ------------------------------------------------------------------ //

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