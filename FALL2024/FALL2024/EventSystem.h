#pragma once
#include <iostream>
#include <functional>
#include <map>
#include <vector>
#include <unordered_map>

class EventSystem
{
private:
	using CallbackVoid = std::function<void()>;
	using CallbackWithIntAndInt = std::function<void(int, int)>;
	using CallbackId = size_t;

	std::map<std::string, std::unordered_map<CallbackId, CallbackVoid>> voidSubscribers;
	std::map<std::string, std::unordered_map<CallbackId, CallbackWithIntAndInt>> intAndIntSubscribers;
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

	CallbackId subscribe(const std::string& eventType, CallbackVoid callback)
	{
		CallbackId id = nextId++;
		voidSubscribers[eventType][id] = callback;
		return id;
	}

	CallbackId subscribe(const std::string& eventType, CallbackWithIntAndInt callback)
	{
		CallbackId id = nextId++;
		intAndIntSubscribers[eventType][id] = callback;
		return id;
	}

	void unsubscribe(const std::string& eventType, CallbackId id);
	void unsubscribeIntAndInt(const std::string& eventType, CallbackId id);
	void notify(const std::string& eventType);
	void notify(const std::string& eventType, int a, int b);
};

