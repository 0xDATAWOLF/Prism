#pragma once
#include <core/events.h>

namespace Prism {

	class InputKeyEvent : public IEvent {

	public:
		inline InputKeyEvent(int key, int scancode, int action, int mods) :
			_key(key), _scancode(scancode), _action(action), _mods(mods) {};
		inline virtual ~InputKeyEvent() {};

		inline int GetKey() { return _key; }
		inline int GetScancode() { return _scancode; }
		inline int GetAction() { return _action; }
		inline int GetMods() { return _mods; }

		EVENT_CLASS_TYPE(InputKeyEvent)

	private:
		int _key;
		int _scancode;
		int _action;
		int _mods;

	};

}