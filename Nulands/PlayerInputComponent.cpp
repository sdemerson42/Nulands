#include "PlayerInputComponent.h"
#include "Entity.h"
#include "PhysicsComponent.h"
#include "AnimatorComponent.h"

FactoryRegistry<PlayerInputComponent> PlayerInputComponent::m_fReg{ "PlayerInput" };

PlayerInputComponent::PlayerInputComponent(Entity *parent) :
	IComponent{ parent }
{
	eventManager.registerFunc(this, &PlayerInputComponent::onInput);
	m_animator = parent->getComponent<AnimatorComponent>();
	m_physics = parent->getComponent<PhysicsComponent>();
}

void PlayerInputComponent::onInput(const Events::InputEvent *evnt)
{
	float x = evnt->iw->x;

	if (abs(m_physics->momentum().x) < 3.0f)
		m_physics->setMomentum(m_physics->momentum().x + x, m_physics->momentum().y);

	if (x < 0)
	{
		m_facing = 0;
		m_animator->play("left");
	}
	else if (x > 0)
	{
		m_animator->play("right");
		m_facing = 1;
	}
	else
	{
		if (m_facing == 0)
		{
			m_animator->play("idleleft");
		}
		else
			m_animator->play("idleright");
	}
}