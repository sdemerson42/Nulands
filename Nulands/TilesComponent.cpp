//#include "TilesComponent.h"
//#include "RenderComponent.h"
//#include "PhysicsComponent.h"
//#include "Entity.h"
//#include "Factory.h"
//
//#include <fstream>
//
//std::istream& operator >> (std::istream& ist, TilesComponent::Tile & t)
//{
//	char c;
//	if (!(ist >> c) || c != '{')
//	{
//		ist.putback(c);
//		ist.clear(ios_base::failbit);
//		return ist;
//	}
//
//	float x, y, w, h;
//
//	ist >> x >> y >> w >> h;
//	t.posRect.x = x;
//	t.posRect.y = y;
//	t.posRect.w = w;
//	t.posRect.h = h;
//
//	ist >> x >> y >> w >> h >> c;
//	t.texRect.x = x;
//	t.texRect.y = y;
//	t.texRect.w = w;
//	t.texRect.h = h;
//
//	if (c == '+') t.solid = true;
//	else t.solid = false;
//
//	ist >> c;
//
//	return ist;
//}
//
//TilesComponent::TilesComponent(Entity *parent, const std::string &fName, std::vector<std::shared_ptr<Entity>> &eVec) :
//	IComponent{ parent }
//{
//	std::ifstream ifs{ "Data\\" + fName };
//	std::string texFName;
//	ifs >> texFName;
//	float ex = parent->position().x;
//	float ey = parent->position().y;
//	while (ifs)
//	{
//		Tile t;
//		ifs >> t;
//		if (!ifs) return;
//		eVec.push_back(std::make_shared<Entity>());
//		Entity *p = eVec[eVec.size() - 1].get();
//		p->setPosition(t.posRect.x, t.posRect.y);
//		p->addComponent<RenderComponent>(p, texFName, t.texRect.x, t.texRect.y, t.texRect.w, t.texRect.h);
//		if (t.solid)
//		{
//			p->addComponent<PhysicsComponent>(p, 0.0f, 0.0f, t.posRect.w, t.posRect.h, false, true, true);
//		}
//	}
//}
//
//void TilesComponent::initialize(const std::vector<std::string> &args)
//{
//
//}
//
//void TilesComponent::outState(std::ostream &ost) const
//{
//	/*
//	for (auto &sp : m_entVec)
//		sp->outState(ost);
//		*/
//}
//
