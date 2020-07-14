#pragma once
#include "core/events.h"
#include "core/input.h"

namespace Prism {

	class KeyHeldEvent : public IEvent {

	public:
		inline KeyHeldEvent(Key k) : _key(k) {};
		inline virtual ~KeyHeldEvent() {};
		inline Key GetKey() { return _key; }

		EVENT_CLASS_TYPE(KeyHeldEvent)

	protected:
		Key _key;

	};

}