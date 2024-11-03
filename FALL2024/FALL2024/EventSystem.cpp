#include "EventSystem.h"

void EventSystem::subscribe(const std::string& eventType, Callback callback) 
{
    subscribers[eventType].push_back(callback);
}

// Unsubscribe from an event
void EventSystem::unsubscribe(const std::string& eventType, Callback callback)
{
    if (subscribers.find(eventType) != subscribers.end()) {
        auto& callbacks = subscribers[eventType];
        // Remove the callback from the vector
        callbacks.erase(std::remove(callbacks.begin(), callbacks.end(), callback), callbacks.end());

        // If no more callbacks are left for the event, remove the event from the map
        if (callbacks.empty()) {
            subscribers.erase(eventType);
        }
    }
}

void EventSystem::notify(const std::string& eventType) 
{
    if (subscribers.find(eventType) != subscribers.end()) 
    {
        for (const auto& callback : subscribers[eventType]) 
        {
            callback();
        }
    }
}