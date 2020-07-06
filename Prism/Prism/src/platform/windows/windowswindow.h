#pragma once
#include <GLFW/glfw3.h>
#include <core/events.h>
#include <core/window.h>
#include <core/renderer/GraphicsContext.h>

namespace Prism {

	/* Creates a Windows platform specific window using GLFW. Initialization is called
	upon construction, deinitialization called during destruction or if window construction
	encounters an error during construction. */
	class WindowsWindow : public Window {
	
	public:
		WindowsWindow(const WindowProperties& winprops);
		inline virtual ~WindowsWindow() { Shutdown(); }
		inline uint32_t GetWidth() override { return _winData.width; }
		inline uint32_t GetHeight() override { return _winData.height; }
		inline float GetDPIWidthScale() override { return _winData.wScale; }
		inline float GetDPIHeightScale() override { return _winData.hScale; }
		inline void SetWidth(uint32_t w) override { _winData.width = w; }
		inline void SetHeight(uint32_t h) override { _winData.height = h; }
		inline bool GetVsync() const override { return _winData.vsyncEnabled; }
		void SetVsync(bool) override;

		/* Returns a void pointer to the GLFW window instance. Ensure type casting is done properly
		with macros otherwise things might go boom. */
		inline void * GetWindowPtr() override { return _glfwWindow; }

		void Update();
	private:
		void Shutdown();

		/* Window data is the container class which contains all property data that WindowsWindow
		uses. The purpose is to decouple the property from the methods so that it can be passed around
		by reference or pointer to GLFW and other pertaining parties. */
		struct WindowData {
			uint32_t width;
			uint32_t height;
			float wScale;
			float hScale;
			std::string title;
			bool vsyncEnabled;

			std::function<void(IEvent*)> callbackfn;
		};

		WindowData _winData;
		GLFWwindow* _glfwWindow{ nullptr };
		GraphicsContext* _context;

	};

}

