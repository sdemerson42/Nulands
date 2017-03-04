#pragma once

#include "IComponent.h"
#include "Events.h"

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
private:
	void onInput(const Events::InputEvent *evnt);
	AnimatorComponent *m_animator;
	PhysicsComponent *m_physics;
	int m_facing{ 1 };
};