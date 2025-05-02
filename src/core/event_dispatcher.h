/**
  ******************************************************************************
  * @file           : event_dispatcher.h
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 25-5-2
  ******************************************************************************
  */

#ifndef THREECPP_EVENT_DISPATCHER_H
#define THREECPP_EVENT_DISPATCHER_H

#include <functional>
#include <memory>
#include <unordered_map>
#include <list>

#include "typeid_provider.h"

namespace three {

    class Event : public TypeIdProvider {
    public:
        Event() = default;

        ~Event() noexcept override = 0;

        InitTypeId(Event);
    };

    class EventDispatcher {
    public:
        using Listener = std::function<void(const std::shared_ptr<Event> &)>;
        using EventTypeId = TypeId;
    public:
        EventDispatcher() = default;

        virtual ~EventDispatcher() noexcept = 0;

        void addEventListener(EventTypeId eventId, const Listener &listener);

        std::size_t getListenerCount(EventTypeId eventId) const;

        void clearEventListener(EventTypeId eventId);

        void dispatchEvent(const std::shared_ptr<Event> &event) const;

    private:
        std::unordered_map<TypeId, std::list<Listener>> _listeners{};
    };

}

#endif //THREECPP_EVENT_DISPATCHER_H
