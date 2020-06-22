#pragma once
#include <core/events.h>

namespace Prism {

	class InputCharEvent : public IEvent {

	public:
		inline InputCharEvent(uint32_t c) : _codepoint(c) {};
		inline virtual ~InputCharEvent() {};

		inline uint32_t GetCodepoint() { return _codepoint; };

		EVENT_CLASS_TYPE(InputCharEvent)

	private:
		uint32_t _codepoint;

	};

}
