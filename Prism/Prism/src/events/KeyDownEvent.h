#pragma once
#include "core/events.h"
#include "core/input.h"

namespace Prism {

	class KeyDownEvent : public IEvent {

	public:
		inline KeyDownEvent(Key k) : _key(k) {};
		inline virtual ~KeyDownEvent() {};
		inline Key GetKey() { return _key; }

		EVENT_CLASS_TYPE(KeyDownEvent)

	protected:
		Key _key;

	};

}