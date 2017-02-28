#pragma once

#include "IComponent.h"
#include "GTypes.h"
#include <string>
#include <vector>
#include <memory>

class Entity;

class TilesComponent : public IComponent
{
public:
	TilesComponent(Entity *parent, const std::string &fName);
	struct Tile
	{
		GTypes::Rect texRect;
		GTypes::Rect posRect;
		bool solid;
	};
	void update() override
	{}
private:
	std::vector<std::shared_ptr<Entity>> m_entVec;
};