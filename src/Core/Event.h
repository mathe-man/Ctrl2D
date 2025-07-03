#pragma once
#include <functional>
#include <memory>
#include <typeindex>


// Base event type
struct IEvent
{
    virtual ~IEvent() = default;
};

template <typename T>
struct ValueChangeEvent : IEvent
{
    T pastValue;
    T newValue;
    T difference;

    ValueChangeEvent(const T& past, const T& current, const T& diff)
        : pastValue(past), newValue(current), difference(diff) {}
};



template <typename TEvent>
class Event : public IEvent {
public:
    using Listener = std::function<void(const TEvent&)>;

    void subscribe(const Listener& listener){
        listeners.push_back(listener);
    }

protected:
    void emit(const TEvent& event){
        for (const auto& l : listeners)
            l(event);
    }


    std::vector<Listener> listeners = std::vector<Listener>();

    friend class EventDispatcher;
};


class EventDispatcher {
public:

    template<typename TEvent>
    Event<TEvent>& Get()
    {
        auto key = std::type_index(typeid(TEvent));

        // Create key if it isn't registered yet
        if (events.find(key) == events.end()){
            auto ptr = std::make_unique<Event<TEvent>>();

            std::unique_ptr<IEvent> basePtr(static_cast<IEvent*>(ptr.release()));
            events[key] = std::move(basePtr);
        }

        return *static_cast<Event<TEvent>*>(events[key].get());
    }

    template<typename TEvent>
    void Emit(const TEvent& e){
        Get<TEvent>().emit(e);
    }



private:
    std::unordered_map<std::type_index, std::unique_ptr<IEvent>> events;

};


/*  HOW EVENTS SHOULD BE IMPLEMENTED
 *  This part provide the correct method to add an event to a class
 *  Objective:
 *  Keep the event emit private,
 *  subscribing to the event should be public.
 *  Note that the Transform2D component is also a good exemple for that
 *  Code exemple:
 *
struct MyClassInstantiatedEvent  : IEvent {}
struct MyClassDeConstructedEvent : IEvent {}


class MyClass {
private:
    EventDispatcher eventsDisp = EventDispatcher();

public:
    int myId
    MyClass(int id) {
        myId = id;
        eventsDisp.Emit(MyClassInstantiatedEvent{});
    }

    ~MyClass { eventsDisp.Emit(MyClassDeConstructedEvent{}); }


    template<typename eventType>
    static void SubToEvent(std::function<void(const eventType&)> function) {
        eventsDisp.Get<eventType>().subscribe(function);
    }
}

*/






