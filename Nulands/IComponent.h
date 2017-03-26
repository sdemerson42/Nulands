#pragma once

#include "EventManager.h"
#include "AutoList.h"
#include <vector>
#include <string>

class Entity;

class IComponent: public EventHandler, public AutoList<IComponent>
{
public:
	IComponent(Entity *parent) :
		m_parentEntity{ parent }
	{}
	virtual ~IComponent()
	{}
	virtual void initialize(const std::vector<string> &)
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
	virtual void outState(std::ostream &ost) const = 0;
private:
	Entity *m_parentEntity;
	bool m_active{ true };
};

std::ostream &operator << (std::ostream &ost, const IComponent &c);

template<typename T>
IComponent *makeComponent(Entity *e)
{
	return new T{ e };
}
