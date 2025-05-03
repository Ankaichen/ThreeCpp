/**
  ******************************************************************************
  * @file           : event_dispatcher.h
  * @author         : An Kaichen
  * @brief          : Provides the Event and EventDispatcher classes for event handling and listener management.
  *                   The `Event` class serves as a base class for creating specific events, while the
  *                   `EventDispatcher` class allows for managing event listeners and dispatching events to them.
  *                   Listeners are callback functions that are triggered when a specific event is dispatched.
  * @attention      : The `Event` class should be subclassed to create custom events. The `EventDispatcher`
  *                   class manages listeners (callbacks) for those events and provides functions to add,
  *                   remove, and count listeners. The event system relies on `TypeId` to uniquely identify
  *                   different event types.
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

    /**
     * Event base class, inherited in subclasses, used to define specific events
     */
    class Event : public TypeIdProvider {
    public:
        Event() = default;

        ~Event() noexcept override = 0;

        InitTypeId(Event);
    };

    /**
     * This class allows to dispatch event and run callback function (Listener).
     */
    class EventDispatcher {
    public:
        /**
         * The type of callback function.
         */
        using Listener = std::function<void(const std::shared_ptr<Event> &)>;
        using EventTypeId = TypeId;
    public:
        EventDispatcher() = default;

        virtual ~EventDispatcher() noexcept = 0;

        /**
         * Add a Listener to the event of eventId.
         * @param eventId the TypeId of event.
         * @param listener the callback function set to event.
         */
        void addEventListener(EventTypeId eventId, const Listener &listener);

        /**
         * Get the count of Listener of an event.
         * @param eventId the TypeId of event.
         * @return the count of Listener.
         */
        std::size_t getListenerCount(EventTypeId eventId) const;

        /**
         * Clear all Listeners of an event.
         * @param eventId the TypeId of event.
         */
        void clearEventListener(EventTypeId eventId);

        /**
         * Dispatches an event object.
         * @param event an event object
         */
        void dispatchEvent(const std::shared_ptr<Event> &event) const;

    private:
        std::unordered_map<TypeId, std::list<Listener>> _listeners{};
    };

}

#endif //THREECPP_EVENT_DISPATCHER_H
