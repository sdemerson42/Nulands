#pragma once

#include "EventManager.h"

class ISystem : public EventHandler
{
public:
	virtual ~ISystem()
	{}
	virtual void update() = 0;
};
