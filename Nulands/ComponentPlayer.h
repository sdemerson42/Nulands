#pragma once

#include "IComponent.h"

class ComponentPlayer : public IComponent
{
public:
	ComponentPlayer(Entity* parent) :
		IComponent{ parent }
	{}
	void update() override;
private:

};
