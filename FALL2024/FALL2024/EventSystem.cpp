#include "EventSystem.h"

// Unsubscribe from an event using the unique ID
void EventSystem::unsubscribe(const std::string& eventType, CallbackId id) 
{
    if (subscribers.find(eventType) != subscribers.end()) 
    {
        subscribers[eventType].erase(id);
        if (subscribers[eventType].empty()) 
        {
            subscribers.erase(eventType);
        }
    }
}

// Notify all subscribers of an event
void EventSystem::notify(const std::string& eventType) 
{
    if (subscribers.find(eventType) != subscribers.end()) 
    {
        for (const auto& [id, callback] : subscribers[eventType]) 
        {
            callback();
        }
    }
}