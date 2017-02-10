#pragma once

#include "IComponent.h"
#include "GTypes.h"

class ComponentRoom : public IComponent
{
public:
	ComponentRoom(Entity* parent, GTypes::EntityGuid nextRoom) :
		IComponent{ parent }, m_nextRoom{ nextRoom }
	{}
	void update() override
	{}
private:
	GTypes::EntityGuid m_nextRoom;
};
