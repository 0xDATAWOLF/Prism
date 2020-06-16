#pragma once
#include "../core.h"

namespace Prism {

    enum class IEvent {};

    class IObserver {
    public:
        IObserver();
        ~IObserver();
        virtual void OnEvent(IEvent ev) {}
    };

    class ISubject {
    public:
        ISubject();
        virtual ~ISubject();
        
        /** Dispatches events to the observers in the collection. */
        inline virtual void Dispatch(IEvent ev) {
            for (auto a : _observers) a->OnEvent(ev);
        }
        
        /** Attaches an observer to the collection. */
        inline void Attach(IObserver* obs) {
            for (auto a : _observers) // determine if the observer is unique.
                if (a == obs) return;
            _observers.push_back(obs);
        };
        
        /** Detaches an observer from the collection. */
        inline void Detach(IObserver* obs) {
            for (auto i = 0; i < _observers.size(); i++) // search for element and delete at pos.
                if (obs == _observers[i]) _observers.erase(_observers.begin()+i);
            return;
        };
    protected:
        std::vector<IObserver*> _observers;
    };

}
