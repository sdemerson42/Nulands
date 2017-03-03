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
		if (!p->m_static && p->active())
			adjustForces(p);
	}
	checkCollisions();
}

void PhysicsSystem::adjustForces(PhysicsComponent *p)
{
	p->setMomentum(constrainToMax(p->m_momentum.x), constrainToMax(p->m_momentum.y));
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
		if (!p->m_static && p->active())
		{
			float xm = p->m_momentum.x;
			float ym = p->m_momentum.y;
			m_dragFlag = false;
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

			if (m_dragFlag)
			{
				float uxm = p->m_momentum.x;
				if (uxm > 0)
				{
					uxm -= m_drag;
					if (uxm < 0) uxm = 0.0f;
				}
				else if (uxm < 0)
				{
					uxm += m_drag;
					if (uxm > 0) uxm = 0.0f;
				}
				p->m_momentum.x = uxm;
			}
		}
	}

	delete m_qt;
}

bool PhysicsSystem::collisionX(PhysicsComponent *p1, PhysicsComponent *p2, float xStartMomentum)
{	
	float px1 = p1->getParent()->position().x;
	float py1 = p1->getParent()->position().y;
	float x1 = px1 + p1->m_collisionBox.x;
	float y1 = py1 + p1->m_collisionBox.y;
	float x2 = p2->getParent()->position().x + p2->m_collisionBox.x;
	float y2 = p2->getParent()->position().y + p2->m_collisionBox.y;
	
	GTypes::Rect r1{ x1 + p1->m_momentum.x, y1, p1->m_collisionBox.w, p1->m_collisionBox.h };
	GTypes::Rect r2{ x2, y2, p2->m_collisionBox.w, p2->m_collisionBox.h };
	if (collide(r1, r2))
	{
		if (p1->m_solid && p2->m_solid)
		{
			float deltaX = 0;
			if (xStartMomentum > 0)
				deltaX = (x2 - r1.w) - x1;
			if (xStartMomentum < 0)
				deltaX = (x2 + r2.w) - x1;
			p1->getParent()->setPosition(px1 + deltaX, py1);
			p1->setMomentum(0.0f, p1->m_momentum.y);
			return true;
		}
	}
	return false;
}

bool PhysicsSystem::collisionY(PhysicsComponent *p1, PhysicsComponent *p2, float yStartMomentum)
{
	float px1 = p1->getParent()->position().x;
	float py1 = p1->getParent()->position().y;
	float x1 = px1 + p1->m_collisionBox.x;
	float y1 = py1 + p1->m_collisionBox.y;
	float x2 = p2->getParent()->position().x + p2->m_collisionBox.x;
	float y2 = p2->getParent()->position().y + p2->m_collisionBox.y;

	GTypes::Rect r1{ x1, y1 + p1->m_momentum.y, p1->m_collisionBox.w, p1->m_collisionBox.h };
	GTypes::Rect r2{ x2, y2, p2->m_collisionBox.w, p2->m_collisionBox.h };

	if (collide(r1, r2))
	{

		if (p1->m_solid && p2->m_solid)
		{
			float deltaY = 0;
			if (yStartMomentum > 0)
			{
				deltaY = (y2 - r1.h) - y1;
				if (deltaY == 0.0f)
					m_dragFlag = true;
			}
			if (yStartMomentum < 0)
				deltaY = (y2 + r2.h) - y1;
			p1->getParent()->setPosition(px1, py1 + deltaY);
			p1->setMomentum(p1->m_momentum.x, 0.0f);
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
	float _x = constrainToMax(p->m_momentum.x + x);
	float _y = constrainToMax(p->m_momentum.y + y);
	p->setMomentum(_x, _y);
}

float PhysicsSystem::constrainToMax(float m)
{
	if (abs(m) > m_maxVelocity)
	{
		if (m < 0) m = -1.0f * m_maxVelocity;
		else m = m_maxVelocity;
	}
	return m;
}