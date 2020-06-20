#pragma once
#include <core/logger.h>
#include <core/events.h>

namespace Prism {

	class NullEvent : public IEvent {
	public:
		inline NullEvent() { CORE_WARN("A null event has been constructed. Was this intended?"); }
		inline virtual ~NullEvent() {};

		EVENT_CLASS_TYPE(NullEvent)
	};

}