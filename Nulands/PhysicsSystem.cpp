#include "PhysicsSystem.h"
#include "PhysicsComponent.h"
#include "Entity.h"

void PhysicsSystem::update()
{
	for (int i = 0; i < AutoList<PhysicsComponent>::size(); ++i)
	{
		m_pc = AutoList<PhysicsComponent>::get(i);
		move();
	}
}

void PhysicsSystem::move()
{
	m_pc->setMomentum(constrainToMax(m_pc->momentum().x), constrainToMax(m_pc->momentum().y));
	applyGravity();
	collisionX();
	collisionY();
}

void PhysicsSystem::applyGravity()
{
	if (m_pc->usesGravity())
		applyForce(0.0f, m_gravity);
}

void PhysicsSystem::collisionX()
{

	if (m_pc->momentum().x == 0) return;

	float cx = m_pc->getParent()->position().x + m_pc->momentum().x;
	float x1 = cx + m_pc->collisionBox().x;
	float w1 = m_pc->collisionBox().w;

	float cy = m_pc->getParent()->position().y + m_pc->momentum().y;
	float y1 = cy + m_pc->collisionBox().y;
	float h1 = m_pc->collisionBox().h;

	bool didCollide = false;

	for (int i = 0; i < AutoList<PhysicsComponent>::size(); ++i)
	{
		auto p = AutoList<PhysicsComponent>::get(i);
		if (p != m_pc)
		{
			float x2 = p->getParent()->position().x + p->collisionBox().x;
			float w2 = p->collisionBox().w;
			float y2 = p->getParent()->position().y + p->collisionBox().y;
			float h2 = p->collisionBox().h;

			if (x1 + w1 > x2 && x1 < x2 + w2 && y1 + h1 > y2 && y1 < y2 + h2)
			{
				if (m_pc->momentum().x > 0)
				{
					// Right-moving collision message
					
					if (m_pc->solid() && p->solid())
					{
						m_pc->getParent()->setPosition(x2 - w1, m_pc->getParent()->position().y);
						m_pc->setMomentum(0.0f, m_pc->momentum().y);
						didCollide = true;
					}
				}
				else
				{
					// Left-moving collision message

					if (m_pc->solid() && p->solid())
					{
						m_pc->getParent()->setPosition(x2 + w2, m_pc->getParent()->position().y);
						m_pc->setMomentum(0.0f, m_pc->momentum().y);
						didCollide = true;
					}
				}
			}
		}
	}
	if (!didCollide) m_pc->getParent()->addPosition(m_pc->momentum().x, 0.0f);

}

void PhysicsSystem::collisionY()
{

	if (m_pc->momentum().y == 0) return;


	float cx = m_pc->getParent()->position().x + m_pc->momentum().x;
	float x1 = cx + m_pc->collisionBox().x;
	float w1 = m_pc->collisionBox().w;

	float cy = m_pc->getParent()->position().y + m_pc->momentum().y;
	float y1 = cy + m_pc->collisionBox().y;
	float h1 = m_pc->collisionBox().h;
	bool didCollide = false;

	for (int i = 0; i < AutoList<PhysicsComponent>::size(); ++i)
	{
		auto p = AutoList<PhysicsComponent>::get(i);
		if (p != m_pc)
		{
			float x2 = p->getParent()->position().x + p->collisionBox().x;
			float w2 = p->collisionBox().w;
			float y2 = p->getParent()->position().y + p->collisionBox().y;
			float h2 = p->collisionBox().h;

			if (x1 + w1 > x2 && x1 < x2 + w2 && y1 + h1 > y2 && y1 < y2 + h2)
			{
				if (m_pc->momentum().y > 0)
				{
					// Down-moving collision message

					if (m_pc->solid() && p->solid())
					{
						m_pc->getParent()->setPosition(m_pc->getParent()->position().x, y2 - h1);
						m_pc->setMomentum(m_pc->momentum().x, 0.0f);
						didCollide = true;
					}
				}
				else
				{
					// Up-moving collision message

					if (m_pc->solid() && p->solid())
					{
						m_pc->getParent()->setPosition(m_pc->getParent()->position().x, y2 + h2);
						m_pc->setMomentum(m_pc->momentum().x, 0.0f);
						didCollide = true;
					}
				}
			}
		}
	}
	if (!didCollide) m_pc->getParent()->addPosition(0.0f, m_pc->momentum().y);
}

void PhysicsSystem::applyForce(float x, float y)
{
	float _x = constrainToMax(m_pc->momentum().x + x);
	float _y = constrainToMax(m_pc->momentum().y + y);
	m_pc->setMomentum(_x, _y);
}

float PhysicsSystem::constrainToMax(float m)
{
	if (abs(m) > m_maxVelocity)
	{
		if (m < 0) m = 1.0f * m_maxVelocity;
		else m = m_maxVelocity;
	}
	return m;
}