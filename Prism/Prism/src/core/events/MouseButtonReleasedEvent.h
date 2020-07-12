#pragma once
#include <core/events.h>

namespace Prism {

	class MouseButtonReleasedEvent : public IEvent {

	public:
		inline MouseButtonReleasedEvent(MouseBtn button) : _button(button) {};
		inline virtual ~MouseButtonReleasedEvent() {};
		inline MouseBtn GetButton() { return _button; }

		EVENT_CLASS_TYPE(MouseButtonReleasedEvent)

	protected:
		MouseBtn _button;

	};

}