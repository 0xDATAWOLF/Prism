#pragma once
#include <core/core.h>
#include <core/events.h>

namespace Prism {

	class Window : public ISubject {

	public:
		inline virtual ~Window() {};
		virtual uint32_t GetWidth() = 0;
		virtual uint32_t GetHeight() = 0;
		virtual float GetDPIWidthScale() = 0;
		virtual float GetDPIHeightScale() = 0;
		virtual void SetWidth(uint32_t) = 0;
		virtual void SetHeight(uint32_t) = 0;
		virtual bool IsVsyncEnabled() const = 0;
		virtual void SetVsync(bool) = 0;

		virtual void Update() = 0;
		virtual void * GetWindowPtr() = 0;

		/* Creates and returns a window pointer based on the platform that the project is built on. */
		static std::unique_ptr<Window> Create(uint32_t width, uint32_t height, std::string windowTitle);

	};

}