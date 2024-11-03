#include "EventSystem.h"

// Unsubscribe from an event using the unique ID
void EventSystem::unsubscribe(const std::string& eventType, CallbackId id) 
{
    if (voidSubscribers.find(eventType) != voidSubscribers.end()) 
    {
        voidSubscribers[eventType].erase(id);
        if (voidSubscribers[eventType].empty()) 
        {
            voidSubscribers.erase(eventType);
        }
    }
}

void EventSystem::unsubscribeIntAndInt(const std::string& eventType, CallbackId id)
{
    if (intAndIntSubscribers.find(eventType) != intAndIntSubscribers.end())
    {
        intAndIntSubscribers[eventType].erase(id);
        if (intAndIntSubscribers[eventType].empty())
        {
            intAndIntSubscribers.erase(eventType);
        }
    }
}

// Notify all subscribers of an event
void EventSystem::notify(const std::string& eventType) 
{
    if (voidSubscribers.find(eventType) != voidSubscribers.end()) 
    {
        for (const auto& [id, callback] : voidSubscribers[eventType]) 
        {
            callback();
        }
    }
}

void EventSystem::notify(const std::string& eventType, int a, int b)
{
    if (intAndIntSubscribers.find(eventType) != intAndIntSubscribers.end())
    {
        for (const auto& [id, callback] : intAndIntSubscribers[eventType])
        {
            callback(a, b);
        }
    }
}