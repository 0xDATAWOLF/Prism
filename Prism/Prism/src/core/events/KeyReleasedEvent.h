#pragma once
#include <core/events.h>

namespace Prism {

	class KeyReleasedEvent : public IEvent {

	public:
		inline KeyReleasedEvent(int16_t key) : _keycode(key) {};
		inline virtual ~KeyReleasedEvent() {};
		inline int16_t GetKey() { return _keycode; }

		EVENT_CLASS_TYPE(KeyReleasedEvent)

	protected:
		int16_t _keycode;

	};

}
