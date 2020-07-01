#pragma once
#include <core/events.h>

namespace Prism {

	class KeyTypedEvent : public IEvent {

	public:
		inline KeyTypedEvent(uint32_t c) : _keycode(c) {};
		inline virtual ~KeyTypedEvent() {};

		inline uint32_t GetKeyCode() { return _keycode; };

		EVENT_CLASS_TYPE(KeyTypedEvent)

	private:
		uint32_t _keycode;

	};

}
