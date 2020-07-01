#pragma once
#include <core/core.h>
#include <core/events.h>

namespace Prism {

	/* A container for window properties which holds basic information about the window such as
	width, height, title, and vsync status. It used as a means of passing around window properties
	without hauling the entire window class with it. */
	struct WindowProperties {
		uint32_t width;
		uint32_t height;
		std::string title;
		bool vsyncEnabled;

		/* Constructs window properties with default values. */
		inline WindowProperties(uint32_t w = 1280, uint32_t h = 720, std::string t = "Prism Engine | 0xDATAWOLF")
			: width(w), height(h), title(t), vsyncEnabled(true) {}
	};

	/* Window is an interface class that is used as the base class for platform-specific window implementations.
	See <platform/[platform]> for each platforms' specific window code. The static method Window::Create() handles
	the platform agnostic implementation of the code. */
	class Window : public ISubject {

	public:
		inline virtual ~Window() {};
		virtual uint32_t GetWidth() = 0;
		virtual uint32_t GetHeight() = 0;
		virtual float GetDPIWidthScale() = 0;
		virtual float GetDPIHeightScale() = 0;
		virtual void SetWidth(uint32_t) = 0;
		virtual void SetHeight(uint32_t) = 0;
		virtual bool GetVsync() const = 0;
		virtual void SetVsync(bool) = 0;

		virtual void Update() = 0;
		virtual void * GetWindowPtr() = 0;

		/* Creates and returns a window pointer based on the platform that the project is built on. */
		static std::unique_ptr<Window> Create(const WindowProperties & winprops = WindowProperties());

	};

}