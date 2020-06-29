#pragma once
#include <core/core.h>
#include <core/logger.h>
#include <core/events.h>
#include <core/window.h>
#include <core/layerstack.h>

int main(int argc, char** argv);

namespace Prism {

	/* Application is the core base class of the Prism Engine. It contains all the
	functionality to interact with the engine as well as provide */
	class Application : public IObserver {

	public:
		friend int ::main(int argc, char** argv);

		Application(uint32_t, uint32_t, std::string);
		virtual ~Application();
		
		template <class L> void PushLayer();
		void PopLayer(Layer*);

		inline static Application& Get() { return *_singletonInstance; };

	private:
		void OnEvent(IEvent*);
		void Run(); // Used in main

		std::unique_ptr<LayerStack> _layerStack;
		std::unique_ptr<Window> _window;
		bool _running = true;

	private:
		static Application* _singletonInstance;

	};

	// This is the user-defined entry point for the Prism Engine. The defined function must return a
	// a heap allocated Prism::Application user-defined derived class.
	Application* CreateApplication();

	template <class L>
	inline void Application::PushLayer() {
		_layerStack->PushLayer<L>(); //fwd
	}

}