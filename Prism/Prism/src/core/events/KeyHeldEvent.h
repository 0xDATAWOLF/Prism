#pragma once
#include <core/events.h>

namespace Prism {

	class KeyHeldEvent : public IEvent {

	public:
		inline KeyHeldEvent(int16_t key) : _keycode(key) {};
		inline virtual ~KeyHeldEvent() {};
		inline int16_t GetKey() { return _keycode; }

		EVENT_CLASS_TYPE(KeyHeldEvent)

	protected:
		int16_t _keycode;

	};

}