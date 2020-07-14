#pragma once
#include <GLFW/glfw3.h>

#include "core/events.h"
#include "core/window.h"
#include "renderer/graphicscontext.h"

namespace Prism {

	class WindowsWindow : public Window {

		struct WindowData {
			uint32_t width;
			uint32_t height;

			std::string title;

			float wScale;
			float hScale;

			bool vsyncEnabled;

			std::function<void(IEvent*)> callbackfn;
		};
	
	public:
		WindowsWindow(uint32_t width, uint32_t height, std::string windowTitle);
		inline virtual ~WindowsWindow() { Shutdown(); }

		inline float GetDPIWidthScale() override { return _winData.wScale; }
		inline float GetDPIHeightScale() override { return _winData.hScale; }

		inline uint32_t GetWidth() override { return _winData.width; }
		inline uint32_t GetHeight() override { return _winData.height; }
		inline void SetWidth(uint32_t w) override { _winData.width = w; }
		inline void SetHeight(uint32_t h) override { _winData.height = h; }

		inline bool IsVsyncEnabled() const override { return _winData.vsyncEnabled; }
		void SetVsync(bool) override;

		inline void * GetWindowPtr() override { return _glfwWindow; }

		void Update();

	private:
		void Shutdown();

		WindowData _winData;
		GLFWwindow* _glfwWindow{ nullptr };
		GraphicsContext* _context;

	};


}

