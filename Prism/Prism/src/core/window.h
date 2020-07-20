#pragma once
#include "core/core.h"
#include "core/events.h"

namespace Prism {

	// -------------------------------------------------------
	// --- Window --------------------------------------------
	// -------------------------------------------------------

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

		virtual void* GetWindowPtr() = 0;

	public:
		static Scope<Window> Create(uint32_t width, uint32_t height, std::string windowTitle);

	};

}