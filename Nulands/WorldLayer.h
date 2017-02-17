#pragma once

#include "ILayer.h"

class WorldLayer : public ILayer
{
public:
	WorldLayer()
	{
		eventManager.registerFunc(this, &WorldLayer::onPlayerCommand);
	}
	~WorldLayer()
	{
		eventManager.unregisterListener(this);
	}
	void update() override
	{}
private:
	void onPlayerCommand(const Events::PlayerCommandEvent*);
};
