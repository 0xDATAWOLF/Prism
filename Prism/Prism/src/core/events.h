#pragma once
#include <core/core.h>

namespace Prism {

	enum class EventType {
		NullEvent,					// Complete
		WindowCloseEvent,			// Complete
		WindowResizeEvent,			// Complete
		KeyTypedEvent,				// Complete
		KeyDownEvent,				// Complete
		KeyHeldEvent,				// Complete
		KeyReleasedEvent,			// Complete
		MouseButtonDownEvent,		// Complete
		MouseButtonReleasedEvent,	// Complete
		MouseMoveEvent,				// Complete
		MouseScrollEvent,			// Complete
	};

	#define EVENT_CLASS_TYPE(type) \
	inline static EventType GetStaticType() { return EventType::type; }\
	inline virtual EventType GetEventType() const override { return GetStaticType(); }\
	inline virtual std::string GetEventName() const override { return #type; }

	class IEvent {
	public:
		inline IEvent() {};
		virtual ~IEvent() {};
		inline bool IsHandled() { return _dflag_consumed; }
		inline void SetHandled(bool h) { _dflag_consumed = h; }

		virtual EventType GetEventType() const = 0;
		virtual std::string GetEventName() const = 0;

	protected:
		bool _dflag_consumed{ false };

	};

	class IObserver {
	public:
		~IObserver() {};
		virtual void OnEvent(IEvent* ev) { return; }
	};

	class IDispatcher {

	public:
		inline IDispatcher(IEvent * e) : _e(e) {};
		inline virtual ~IDispatcher() {};

		template <class E, typename R>
		bool Forward(const R& func) {
			if (_e->GetEventType() == E::GetStaticType()) {
				_e->SetHandled(func(static_cast<E*>(_e)));
				return true;
			}
			return false;
		}

	protected:
		IEvent* _e;

	};

	class ISubject {
	public:
		virtual ~ISubject() {};

		inline void Send(IEvent * ev) {
			for (auto a : _observers) a->OnEvent(ev);
		}

		inline void Attach(IObserver* obs) {
			for (auto a : _observers)
				if (a == obs) return;
			_observers.push_back(obs);
		};

		inline virtual void Detach(IObserver* obs) {
			for (auto i = 0; i < _observers.size(); i++)
				if (obs == _observers[i]) _observers.erase(_observers.begin()+i);
			return;
		};

	protected:
		std::vector<IObserver*> _observers;
	};

}

// --- Events ------------------------------------
#include <core/events/NullEvent.h>
#include <core/events/WindowCloseEvent.h>
#include <core/events/WindowResizeEvent.h>
#include <core/events/KeyTypedEvent.h>
#include <core/events/KeyDownEvent.h>
#include <core/events/KeyHeldEvent.h>
#include <core/events/KeyReleasedEvent.h>
#include <core/events/MouseButtonDownEvent.h>
#include <core/events/MouseButtonReleasedEvent.h>
#include <core/events/MouseMoveEvent.h>
#include <core/events/MouseScrollEvent.h>