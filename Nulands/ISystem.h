#pragma once

#include "EventHandler.h"

class ISystem : public EventHandler
{
public:
	virtual ~ISystem()
	{}
	virtual void update() = 0;
};
