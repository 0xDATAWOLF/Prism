#pragma once
#include <core/events.h>

namespace Prism {

	class InputMouseScrollEvent : public IEvent {

	public:
		inline InputMouseScrollEvent(double xpos, double ypos) {};
		inline virtual ~InputMouseScrollEvent() {};

		inline double GetXpos() { return _xpos; }
		inline double GetYpos() { return _ypos; }

		EVENT_CLASS_TYPE(InputMouseScrollEvent)

	private:
		double _xpos;
		double _ypos;

	};

}