#pragma once

#include "ILayer.h"

class WorldLayer : public ILayer
{
public:
	WorldLayer()
	{
		registerFunc(this, &WorldLayer::onPlayerCommand);
	}
	void update() override
	{}
private:
	void onPlayerCommand(const Events::PlayerCommandEvent*);
};
