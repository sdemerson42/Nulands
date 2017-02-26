#include "PhysicsSystem.h"
#include "PhysicsComponent.h"
#include "Entity.h"
#include "QuadTree.h"
#include <iostream>

void PhysicsSystem::update()
{
	for (int i = 0; i < AutoList<PhysicsComponent>::size(); ++i)
	{
		auto p = AutoList<PhysicsComponent>::get(i);
		if (!p->isStatic() && p->active())
			adjustForces(p);
	}
	checkCollisions();
}

void PhysicsSystem::adjustForces(PhysicsComponent *p)
{
	p->setMomentum(constrainToMax(p->momentum().x), constrainToMax(p->momentum().y));
	applyGravity(p);
}

void PhysicsSystem::applyGravity(PhysicsComponent *p)
{
	if (p->usesGravity())
		applyForce(p, 0.0f, m_gravity);
}

void PhysicsSystem::checkCollisions()
{
	m_qt = new QuadTree(0, 0, 800, 600);
	for (int i = 0; i < AutoList<PhysicsComponent>::size(); ++i)
		m_qt->insert(AutoList<PhysicsComponent>::get(i));

	for (int i = 0; i < AutoList<PhysicsComponent>::size(); ++i)
	{
		auto p = AutoList<PhysicsComponent>::get(i);
		if (!p->isStatic() && p->active())
		{
			float xm = p->momentum().x;
			float ym = p->momentum().y;
			vector<PhysicsComponent *> v;
			m_qt->retrieve(v, p);
			for (auto pp : v)
			{
				if (pp->active())
				{
					if (collisionX(p, pp, xm) || collisionY(p, pp, ym))
					{
						// Broadcast message
					}
				}
			}

			p->getParent()->addPosition(p->momentum().x, p->momentum().y);
		}
	}


	delete m_qt;
}

bool PhysicsSystem::collisionX(PhysicsComponent *p1, PhysicsComponent *p2, float xStartMomentum)
{	
	float px1 = p1->getParent()->position().x;
	float py1 = p1->getParent()->position().y;
	float x1 = px1 + p1->collisionBox().x;
	float y1 = py1 + p1->collisionBox().y;
	float x2 = p2->getParent()->position().x + p2->collisionBox().x;
	float y2 = p2->getParent()->position().y + p2->collisionBox().y;
	
	GTypes::Rect r1{ x1 + p1->momentum().x, y1, p1->collisionBox().w, p1->collisionBox().h };
	GTypes::Rect r2{ x2, y2, p2->collisionBox().w, p2->collisionBox().h };
	if (collide(r1, r2))
	{
		if (p1->solid() && p2->solid())
		{
			float deltaX = 0;
			if (xStartMomentum > 0)
				deltaX = (x2 - r1.w) - x1;
			if (xStartMomentum < 0)
				deltaX = (x2 + r2.w) - x1;
			p1->getParent()->setPosition(px1 + deltaX, py1);
			p1->setMomentum(0.0f, p1->momentum().y);
			return true;
		}
	}
	return false;
}

bool PhysicsSystem::collisionY(PhysicsComponent *p1, PhysicsComponent *p2, float yStartMomentum)
{
	float px1 = p1->getParent()->position().x;
	float py1 = p1->getParent()->position().y;
	float x1 = px1 + p1->collisionBox().x;
	float y1 = py1 + p1->collisionBox().y;
	float x2 = p2->getParent()->position().x + p2->collisionBox().x;
	float y2 = p2->getParent()->position().y + p2->collisionBox().y;

	GTypes::Rect r1{ x1, y1 + p1->momentum().y, p1->collisionBox().w, p1->collisionBox().h };
	GTypes::Rect r2{ x2, y2, p2->collisionBox().w, p2->collisionBox().h };
	if (collide(r1, r2))
	{

		if (p1->solid() && p2->solid())
		{
			float deltaY = 0;
			if (yStartMomentum > 0)
				deltaY = (y2 - r1.h) - y1;
			if (yStartMomentum < 0)
				deltaY = (y2 + r2.h) - y1;
			p1->getParent()->setPosition(px1, py1 + deltaY);
			p1->setMomentum(p1->momentum().x, 0.0f);
			return true;
		}
	}
	return false;
}

bool PhysicsSystem::collide(const GTypes::Rect &r1, const GTypes::Rect &r2)
{
	return (r1.x + r1.w > r2.x && r1.x < r2.x + r2.w && r1.y + r1.h > r2.y && r1.y < r2.y + r2.h);
}

void PhysicsSystem::applyForce(PhysicsComponent *p, float x, float y)
{
	float _x = constrainToMax(p->momentum().x + x);
	float _y = constrainToMax(p->momentum().y + y);
	p->setMomentum(_x, _y);
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