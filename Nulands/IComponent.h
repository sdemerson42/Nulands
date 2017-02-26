#pragma once

#include "EventManager.h"
#include "AutoList.h"

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
	Entity *getParent() const
	{
		return m_parentEntity;
	}
	void setActive(bool b)
	{
		m_active = b;
	}
	bool active() const
	{
		return m_active;
	}
private:
	Entity *m_parentEntity;
	bool m_active{ true };
};