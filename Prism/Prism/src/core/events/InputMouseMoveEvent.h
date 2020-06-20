#pragma once
#include <core/events.h>

namespace Prism {

	class InputMouseMoveEvent : public IEvent {

	public:
		inline InputMouseMoveEvent(double xpos, double ypos) : _xpos(xpos), _ypos(ypos) {};
		inline virtual ~InputMouseMoveEvent() {};

		inline double GetXpos() { return _xpos; }
		inline double GetYpos() { return _ypos; }

		EVENT_CLASS_TYPE(InputMouseMoveEvent)

	private:
		double _xpos;
		double _ypos;

	};

}