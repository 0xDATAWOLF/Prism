#pragma once
#include <core/events.h>

namespace Prism {

	class InputMouseButtonEvent : public IEvent {

	public:
		inline InputMouseButtonEvent(int button, int action, int mods) : _button(button), _action(action), _mods(mods) {};
		inline virtual ~InputMouseButtonEvent() {};

		inline int GetButton() { return _button; }
		inline int GetAction() { return _action; }
		inline int GetMods() { return _mods; }

		EVENT_CLASS_TYPE(InputMouseButtonEvent)

	private:
		int _button;
		int _action;
		int _mods;

	};

}

