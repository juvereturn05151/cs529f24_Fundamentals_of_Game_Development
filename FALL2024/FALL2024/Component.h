#pragma once
#include "GameObject.h"

class Component
{
	protected:
		GameObject* owner;
		bool isActive;
	public:
		Component(GameObject& _owner);
		virtual void initialize() = 0;
		virtual void update() = 0;
		virtual ~Component();

		void setIsActive(bool active);
};

