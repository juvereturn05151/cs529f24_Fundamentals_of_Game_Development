#pragma once
#include <iostream>
#include <functional>
#include <map>
#include <vector>

class EventSystem
{
private:
	using Callback = std::function<void()>;
	using CallbackId = size_t;
	std::map<std::string, std::unordered_map<CallbackId, Callback>> subscribers;
	CallbackId nextId = 0;

	// Private constructor to prevent instantiation
	EventSystem() = default;

	// Delete copy constructor and assignment operator
	EventSystem(const EventSystem&) = delete;
	EventSystem& operator=(const EventSystem&) = delete;

public:
	static EventSystem& getInstance() 
	{
		static EventSystem instance;
		return instance;
	}

	CallbackId subscribe(const std::string& eventType, Callback callback)
	{
		CallbackId id = nextId++;
		subscribers[eventType][id] = callback;
		return id;
	}

	void unsubscribe(const std::string& eventType, CallbackId id);
	void notify(const std::string& eventType);
};

