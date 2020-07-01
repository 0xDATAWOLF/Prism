#pragma once
#include <core/events.h>

namespace Prism {

	class MouseButtonReleasedEvent : public IEvent {

	public:
		inline MouseButtonReleasedEvent(int16_t button) : _button(button) {};
		inline virtual ~MouseButtonReleasedEvent() {};
		inline int16_t GetButton() { return _button; }

		EVENT_CLASS_TYPE(MouseButtonReleasedEvent)

	protected:
		int16_t _button;

	};

}