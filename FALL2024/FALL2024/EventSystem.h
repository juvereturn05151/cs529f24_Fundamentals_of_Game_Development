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

public:
	void subscribe(const std::string& eventType, Callback callback);
	void notify(const std::string& eventType);
};

