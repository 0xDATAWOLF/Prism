#pragma once
#include "core/events.h"

namespace Prism {

	class WindowResizeEvent : public IEvent {

	public:
		inline WindowResizeEvent(uint32_t w, uint32_t h) :
			_width(w), _height(h) {};
		inline virtual ~WindowResizeEvent() {};

		inline uint32_t GetWidth() { return _width; }
		inline uint32_t GetHeight() { return _height; }

		EVENT_CLASS_TYPE(WindowResizeEvent)

	private:
		uint32_t _width;
		uint32_t _height;

	};

}