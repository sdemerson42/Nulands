#pragma once

#include "EventHandler.h"

class ILayer: public EventHandler
{
public:
	virtual ~ILayer()
	{}
	virtual void update() = 0;
};