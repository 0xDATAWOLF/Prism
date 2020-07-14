#pragma once
#include "core/events.h"

namespace Prism {

	class MouseMoveEvent : public IEvent {

	public:
		inline MouseMoveEvent(double xpos, double ypos) : _xpos(xpos), _ypos(ypos) {};
		inline virtual ~MouseMoveEvent() {};

		inline double GetXpos() { return _xpos; }
		inline double GetYpos() { return _ypos; }

		EVENT_CLASS_TYPE(MouseMoveEvent)

	private:
		double _xpos;
		double _ypos;

	};

}