#pragma once
#include <GLFW/glfw3.h>

#include "core/core.h"
#include "core/events.h"
#include "core/window.h"
#include "renderer/graphicscontext.h"

namespace Prism {

	// -------------------------------------------------------
	// --- Window Data ---------------------------------------
	// -------------------------------------------------------

	struct WindowData {
		uint32_t width;
		uint32_t height;
		std::string title;
		float wScale;
		float hScale;
		bool vsyncEnabled;
		std::function<void(IEvent*)> callbackfn;
	};

	// -------------------------------------------------------
	// --- Windows Window ------------------------------------
	// -------------------------------------------------------

	class WindowsWindow : public Window {
	
	public:
		WindowsWindow(uint32_t width, uint32_t height, std::string windowTitle);
		inline virtual ~WindowsWindow() { Shutdown(); }

		inline float GetDPIWidthScale() override { return WindowDataInstance.wScale; }
		inline float GetDPIHeightScale() override { return WindowDataInstance.hScale; }

		inline uint32_t GetWidth() override { return WindowDataInstance.width; }
		inline uint32_t GetHeight() override { return WindowDataInstance.height; }
		inline void SetWidth(uint32_t w) override { WindowDataInstance.width = w; }
		inline void SetHeight(uint32_t h) override { WindowDataInstance.height = h; }

		inline bool GetVsync() const override { return WindowDataInstance.vsyncEnabled; }
		void SetVsync(bool) override;

		inline void * GetWindowPtr() override { return RawWindowPointer; }

		void Update();

	private:
		void Shutdown();

	private:
		WindowData WindowDataInstance;
		GLFWwindow* RawWindowPointer{ nullptr };
		Ref<GraphicsContext> _context;

	};


}

