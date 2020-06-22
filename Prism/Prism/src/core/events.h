#pragma once
#include <core/core.h>

namespace Prism {

	enum class EventType {
		NullEvent, WindowCloseEvent, WindowResizeEvent,
		InputCharEvent, InputKeyEvent, InputMouseMoveEvent,
		InputMouseButtonEvent, InputMouseScrollEvent
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

		/* The OnEvent method captures all events that have been dispatched to it by ISubject
		implementors if the IObserver implementor is attached to it. When left undefined, the IObserver
		consumes the event and implicitly returns, performing no action on the event. */
		virtual void OnEvent(IEvent* ev) { return;  }

	};

	class ISubject {
	public:
		virtual ~ISubject() {};

		/* Dispatches events to the observers in the collection. */
		inline void Dispatch(IEvent * ev) {
			for (auto a : _observers) a->OnEvent(ev);
		}

		/* Attaches an observer to the collection. */
		inline void Attach(IObserver* obs) {
			for (auto a : _observers) // determine if the observer is unique.
				if (a == obs) return;
			_observers.push_back(obs);
		};

		/* Detaches an observer from the collection. */
		inline void Detach(IObserver* obs) {
			for (auto i = 0; i < _observers.size(); i++) // search for element and delete at pos.
				if (obs == _observers[i]) _observers.erase(_observers.begin()+i);
			return;
		};
	protected:
		std::vector<IObserver*> _observers;
	};

}

// Include the events so that the user doesn't need to include individually.
#include <core/events/NullEvent.h>
#include <core/events/WindowCloseEvent.h>
#include <core/events/WindowResizeEvent.h>
#include <core/events/InputCharEvent.h>
#include <core/events/InputKeyEvent.h>
#include <core/events/InputMouseMoveEvent.h>
#include <core/events/InputMouseButtonEvent.h>
#include <core/events/InputMouseScrollEvent.h>