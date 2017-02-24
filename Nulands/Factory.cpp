#include "Factory.h"

#include "Entity.h"
#include "RenderComponent.h"
#include "PhysicsComponent.h"


void Factory::construct(std::vector<std::shared_ptr<Entity>> &v, EType e, float x, float y)
{
	v.push_back(std::make_shared<Entity>());
	auto p = v[v.size() - 1].get();
	switch (e)
	{
	case EType::TestBox:
	{
		p->addComponent<RenderComponent>(p, "Squares.png", 0, 0, 32, 32);
		p->addComponent<PhysicsComponent>(p, 2, 2, 28, 28, true, true, false, 1.0f, -3.0f);
		p->setPosition(x, y);
		break;
	}
	case EType::TestWall:
	{
		p->addComponent<RenderComponent>(p, "Squares.png", 32, 0, 32, 32);
		p->addComponent<PhysicsComponent>(p, 2, 2, 28, 28, false, true, true);
		p->setPosition(x, y);
		break;
	}
	}
}