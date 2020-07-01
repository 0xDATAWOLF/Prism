#pragma once
#include <core/events.h>

namespace Prism {

	class MouseButtonDownEvent : public IEvent {

	public:
		inline MouseButtonDownEvent(int16_t button) : _button(button) {};
		inline virtual ~MouseButtonDownEvent() {};
		inline int16_t GetButton() { return _button; }

		EVENT_CLASS_TYPE(MouseButtonDownEvent)

	protected:
		int16_t _button;

	};

}