#pragma once

#include "EventManager.h"
#include "BehaviorComponent.h"
#include <string>

class IComponent;

class IBehavior : public EventHandler
{
public:
	IBehavior(IComponent *parent, const std::string &tag) :
		m_parent{ parent }, m_tag{ tag }
	{}
	virtual ~IBehavior()
	{}
	IComponent *getParent() const
	{
		return m_parent;
	}
	virtual void update() = 0;
	std::string getTag()
	{
		return m_tag;
	}
private:
	IComponent *m_parent;
	std::string m_tag;
};