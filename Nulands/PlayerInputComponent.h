#pragma once

#include "IComponent.h"
#include "Events.h"
#include "Factory.h"

class Entity;
class AnimatorComponent;
class PhysicsComponent;

class PlayerInputComponent : public IComponent
{
public:
	PlayerInputComponent(Entity *parent);
	~PlayerInputComponent()
	{
		eventManager.unregisterListener(this);
	}
	void update() override
	{}
	void outState(std::ostream &ost) const override
	{
		ost << "{ PlayerInput }\n";
	}
private:
	void onInput(const Events::InputEvent *evnt);
	AnimatorComponent *m_animator;
	PhysicsComponent *m_physics;
	int m_facing{ 1 };
	static FactoryRegistry<PlayerInputComponent> m_fReg;
};