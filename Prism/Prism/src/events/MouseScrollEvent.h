#pragma once
#include "core/events.h"

namespace Prism {

	class MouseScrollEvent : public IEvent {

	public:
		inline MouseScrollEvent(double xpos, double ypos) : _xpos(xpos), _ypos(ypos) {};
		inline virtual ~MouseScrollEvent() {};

		inline double GetXpos() { return _xpos; }
		inline double GetYpos() { return _ypos; }

		EVENT_CLASS_TYPE(MouseScrollEvent)

	private:
		double _xpos;
		double _ypos;

	};

}