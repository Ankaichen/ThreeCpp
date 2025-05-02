/**
  ******************************************************************************
  * @file           : event_dispatcher.cpp
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 25-5-2
  ******************************************************************************
  */

#include "../event_dispatcher.h"

#include <algorithm>

three::Event::~Event() noexcept = default;

three::EventDispatcher::~EventDispatcher() noexcept = default;

void three::EventDispatcher::addEventListener(three::EventDispatcher::EventTypeId eventId,
                                              const three::EventDispatcher::Listener &listener) {
    auto iter = this->_listeners.find(eventId);
    if (iter == this->_listeners.end()) {
        std::list<Listener> listener_list{};
        listener_list.push_back(listener);
        this->_listeners.insert(std::make_pair(eventId, std::move(listener_list)));
    } else {
        std::list<Listener> &listener_list = iter->second;
        listener_list.push_back(listener);
    }

}

std::size_t three::EventDispatcher::getListenerCount(three::EventDispatcher::EventTypeId eventId) const {
    auto iter = this->_listeners.find(eventId);
    if (iter == this->_listeners.end()) {
        return 0;
    }
    return iter->second.size();
}

void three::EventDispatcher::clearEventListener(three::EventDispatcher::EventTypeId eventId) {
    auto iter = this->_listeners.find(eventId);
    if (iter == this->_listeners.end()) {
        return;
    }
    std::list<Listener> &listener_list = iter->second;
    listener_list.clear();
}

void three::EventDispatcher::dispatchEvent(const std::shared_ptr<Event> &event) const {
    auto iter = this->_listeners.find(event->getTypeId());
    if (iter == this->_listeners.end()) {
        return;
    }
    const std::list<Listener> &listener_list = iter->second;
    std::for_each(listener_list.cbegin(), listener_list.cend(), [&event](const Listener &l) -> void {
        l(event);
    });
}
