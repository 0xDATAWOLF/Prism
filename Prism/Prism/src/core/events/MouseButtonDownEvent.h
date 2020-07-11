#pragma once
#include <core/events.h>
#include <core/input.h>

namespace Prism {

	class MouseButtonDownEvent : public IEvent {

	public:
		inline MouseButtonDownEvent(MouseBtn button) : _button(button) {};
		inline virtual ~MouseButtonDownEvent() {};
		inline MouseBtn GetButton() { return _button; }

		EVENT_CLASS_TYPE(MouseButtonDownEvent)

	protected:
		MouseBtn _button;

	};

}