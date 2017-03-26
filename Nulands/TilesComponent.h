//#pragma once
//
//#include "IComponent.h"
//#include "GTypes.h"
//#include <string>
//#include <vector>
//#include <memory>
//
//class Entity;
//
//class TilesComponent : public IComponent
//{
//public:
//	TilesComponent(Entity *parent, const std::string &fName, std::vector<std::shared_ptr<Entity>> &eVec);
//	void initialize(const std::vector<std::string> &args) override;
//	struct Tile
//	{
//		GTypes::Rect texRect;
//		GTypes::Rect posRect;
//		bool solid;
//	};
//	void update() override
//	{}
//	void outState(std::ostream &ost) const override;
//};