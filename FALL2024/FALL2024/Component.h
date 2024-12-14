#pragma once

#ifndef COMPONENT_H
#define COMPONENT_H

class GameObject;

class Component
{
	protected:
		GameObject* owner;
		bool isActive;
	public:
		Component(GameObject& _owner);
		virtual void initialize() {};
		virtual void update(float deltaTime) {};
		virtual ~Component();

		void setIsActive(bool active);
};

#endif