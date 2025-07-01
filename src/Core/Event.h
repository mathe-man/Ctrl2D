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
