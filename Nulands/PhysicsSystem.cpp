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
		if (!p->isStatic())
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
		int xCol = 0;
		int yCol = 0;
		if (!p->isStatic())
		{
			m_curXm = p->momentum().x;
			m_curYm = p->momentum().y;
			vector<PhysicsComponent *> v;
			m_qt->retrieve(v, p);
			for (auto pp : v)
			{
				if (collisionX(p, pp)) ++xCol;
				if (collisionY(p, pp)) ++yCol;
			}

			p->getParent()->addPosition(p->momentum().x, p->momentum().y);
		}
	}


	delete m_qt;
}

bool PhysicsSystem::collisionX(PhysicsComponent *p1, PhysicsComponent *p2)
{	
	float tx = p1->getParent()->position().x;
	float ty = p1->getParent()->position().y;
	p1->getParent()->addPosition(p1->momentum().x, 0.0f);
	bool colCourse = collide(p1, p2);
	p1->getParent()->setPosition(tx, ty);
	if (colCourse)
	{
		if (p1->solid() && p2->solid())
		{
			float x1 = p1->getParent()->position().x + p1->collisionBox().x;
			float y1 = p1->getParent()->position().y + p1->collisionBox().y;
			float w1 = p1->collisionBox().w;
			float x2 = p2->getParent()->position().x + p2->collisionBox().x;
			float w2 = p2->collisionBox().w;
			float newX = x1;
			if (m_curXm < 0)
			{
				newX = x2 + w2;
			}
			else if (m_curXm > 0)
			{
				newX = x2 - w1;
			}
			p1->getParent()->setPosition(newX, y1);
			p1->setMomentum(0.0f, p1->momentum().y);
		}
	}
	return colCourse;
}

bool PhysicsSystem::collisionY(PhysicsComponent *p1, PhysicsComponent *p2)
{
	float tx = p1->getParent()->position().x;
	float ty = p1->getParent()->position().y;
	p1->getParent()->addPosition(0.0f, p1->momentum().y);
	bool colCourse = collide(p1, p2);
	p1->getParent()->setPosition(tx, ty);
	if (colCourse)
	{
		if (p1->solid() && p2->solid())
		{
			float x1 = p1->getParent()->position().x + p1->collisionBox().x;
			float y1 = p1->getParent()->position().y + p1->collisionBox().y;
			float h1 = p1->collisionBox().h;
			float y2 = p2->getParent()->position().y + p2->collisionBox().y;
			float h2 = p2->collisionBox().h;
			float newY = y1;
			if (m_curYm < 0)
			{
				newY = y2 + h2;
			}
			else if (m_curYm > 0)
			{
				newY = y2 - h1;
			}
			p1->getParent()->setPosition(x1, newY);
			p1->setMomentum(p1->momentum().x, 0.0f);
			int z = 0;
		}
	}
	return colCourse;
}

bool PhysicsSystem::collide(PhysicsComponent *p1, PhysicsComponent *p2)
{
	float x1 = p1->getParent()->position().x + p1->collisionBox().x;
	float y1 = p1->getParent()->position().y + p1->collisionBox().y;
	float w1 = p1->collisionBox().w;
	float h1 = p1->collisionBox().h;
	float x2 = p2->getParent()->position().x + p2->collisionBox().x;
	float y2 = p2->getParent()->position().y + p2->collisionBox().y;
	float w2 = p2->collisionBox().w;
	float h2 = p2->collisionBox().h;

	return (x1 + w1 > x2 && x1 < x2 + w2 && y1 + h1 > y2 && y1 < y2 + h2);
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