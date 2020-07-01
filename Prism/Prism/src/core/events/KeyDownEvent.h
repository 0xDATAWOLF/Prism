#pragma once
#include <core/events.h>

namespace Prism {

	class KeyDownEvent : public IEvent {

	public:
		inline KeyDownEvent(int16_t key) : _keycode(key) {};
		inline virtual ~KeyDownEvent() {};
		inline int16_t GetKey() { return _keycode; }

		EVENT_CLASS_TYPE(KeyDownEvent)

	protected:
		int16_t _keycode;

	};

}