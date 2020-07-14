#pragma once
#include "core/events.h"

namespace Prism {

	class WindowCloseEvent : public IEvent {

	public:
		inline WindowCloseEvent() {};
		inline virtual ~WindowCloseEvent() {};

		EVENT_CLASS_TYPE(WindowCloseEvent)

	};

}