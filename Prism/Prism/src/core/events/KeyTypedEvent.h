#pragma once
#include <core/events.h>
#include <core/input.h>

namespace Prism {

	class KeyTypedEvent : public IEvent {

	public:
		inline KeyTypedEvent(uint32_t k) : _key(k) {};
		inline virtual ~KeyTypedEvent() {};

		inline uint32_t GetKey() { return _key; };

		EVENT_CLASS_TYPE(KeyTypedEvent)

	private:
		uint32_t _key;

	};

}
