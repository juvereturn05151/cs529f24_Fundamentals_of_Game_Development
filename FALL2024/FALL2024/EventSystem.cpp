#include "EventSystem.h"

void EventSystem::subscribe(const std::string& eventType, Callback callback) 
{
    subscribers[eventType].push_back(callback);
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