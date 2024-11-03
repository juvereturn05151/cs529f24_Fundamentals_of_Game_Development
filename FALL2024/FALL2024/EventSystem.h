#pragma once
#include <iostream>
#include <functional>
#include <map>
#include <vector>

class EventSystem
{
private:
	using Callback = std::function<void()>;
	std::map<std::string, std::vector<Callback>> subscribers;

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

	void subscribe(const std::string& eventType, Callback callback);
	void unsubscribe(const std::string& eventType, Callback callback);
	void notify(const std::string& eventType);
};

