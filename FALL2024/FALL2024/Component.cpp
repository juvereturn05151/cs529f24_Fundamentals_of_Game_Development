#include "Component.h"
#include "GameObject.h"

Component::Component(GameObject& _owner) : owner(&_owner), isActive(true) {}


void Component::setIsActive(bool active) 
{
	isActive = active;
}

Component::~Component()
{

}