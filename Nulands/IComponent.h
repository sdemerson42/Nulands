#pragma once

#include "EventHandler.h"

class IComponent: public EventHandler, public AutoList<IComponent>
{
public:
	virtual ~IComponent()
	{}
	virtual void update() = 0;
};