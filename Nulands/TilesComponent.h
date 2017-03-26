#pragma once

#include "IComponent.h"
#include "GTypes.h"
#include <string>
#include <vector>
#include <memory>
#include "Factory.h"

class Entity;

class TilesComponent : public IComponent
{
public:
	friend class Factory;
	TilesComponent(Entity *parent) :
		IComponent{ parent }
	{}
	void initialize(const std::vector<std::string> &args) override;
	struct Tile
	{
		GTypes::Rect texRect;
		GTypes::Rect posRect;
		bool solid;
	};
	void update() override
	{}
	void outState(std::ostream &ost) const override;
private:
	std::vector<std::shared_ptr<Entity>> *m_vecRef;
	static FactoryRegistry<TilesComponent> m_fReg;
};