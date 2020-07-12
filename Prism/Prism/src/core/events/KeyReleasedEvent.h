#pragma once
#include <core/events.h>

namespace Prism {

	class KeyReleasedEvent : public IEvent {

	public:
		inline KeyReleasedEvent(Key k) : _key(k) {};
		inline virtual ~KeyReleasedEvent() {};
		inline Key GetKey() { return _key; }

		EVENT_CLASS_TYPE(KeyReleasedEvent)

	protected:
		Key _key;

	};

}
