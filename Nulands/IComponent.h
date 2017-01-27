#pragma once

#include "EventHandler.h"

class Entity;

class IComponent: public EventHandler, public AutoList<IComponent>
{
public:
	IComponent(Entity *parent) :
		m_parentEntity{ parent }
	{}
	virtual ~IComponent()
	{}
	virtual void update() = 0;
protected:
	Entity *getParent() const
	{
		return m_parentEntity;
	}
private:
	Entity *m_parentEntity;
};