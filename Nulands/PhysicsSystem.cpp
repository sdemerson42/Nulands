#include "PhysicsSystem.h"
#include "PhysicsComponent.h"
#include "Entity.h"
#include <iostream>
#include <set>

PhysicsSystem::PhysicsSystem()
{
	eventManager.registerFunc(this, &PhysicsSystem::onQuadTreeSize);
	m_qt = std::make_unique<QuadTree>();
	m_prox = std::make_unique<ProxMap>();
}

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
	m_qt->clear();
	m_prox->clear();
	m_qt->initialize(0, 0, m_qtSize.x, m_qtSize.y);
	m_prox->initialize(1600, 1600, 96, 96);
	for (int i = 0; i < AutoList<PhysicsComponent>::size(); ++i)
	{
		auto p = AutoList<PhysicsComponent>::get(i);
		if (p->isStatic())
			m_prox->insert(p);
		else
			m_qt->insert(p);
	}

	for (int i = 0; i < AutoList<PhysicsComponent>::size(); ++i)
	{
		auto p = AutoList<PhysicsComponent>::get(i);
		if (!p->m_static && p->active())
		{
			float xm = p->m_momentum.x;
			float ym = p->m_momentum.y;
			m_dragFlag = false;
			vector<PhysicsComponent *> v1;
			m_qt->retrieve(v1, p);
			vector<PhysicsComponent *> v2 = m_prox->retrieve(p);
			
			// X
			
			for (auto pp : v1)
			{
				if (pp->active())
				{
					collisionX(p, pp, xm);
				}
			}
			std::set<PhysicsComponent *> checked;
			for (auto pp : v2)
			{
				if (pp->active() && checked.find(pp) == checked.end() && p->m_momentum.x != 0.0f)
				{
					collisionX(p, pp, xm);
				}
			}

			// Y

			for (auto pp : v1)
			{
				if (pp->active())
				{
					collisionY(p, pp, ym);
				}
			}
			checked.clear();
			for (auto pp : v2)
			{
				if (pp->active() && checked.find(pp) == checked.end() && p->m_momentum.y != 0.0f)
				{
					collisionY(p, pp, ym);
				}
				checked.insert(pp);
			}

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

			p->getParent()->addPosition(p->momentum().x, p->momentum().y);
		}
	}
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
				deltaX = (x2 - r1.w) - x1 - 0.001f;
			if (xStartMomentum < 0)
				deltaX = (x2 + r2.w) - x1 + 0.001f;;
			p1->getParent()->setPosition(px1 + deltaX, py1);
			//m_transX = px1 + deltaX;
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
				if (abs(0.0f - deltaY) <= 0.1f)
					m_dragFlag = true;
				deltaY -= 0.001f;
			}
			if (yStartMomentum < 0)
			{
				deltaY = (y2 + r2.h) - y1 + 0.001f;
			}
			p1->getParent()->setPosition(px1, py1 + deltaY);
			//m_transY = py1 + deltaY;
			p1->setMomentum(p1->m_momentum.x, 0.0f);
			return true;
		}
	}
	return false;
}



bool PhysicsSystem::collide(const GTypes::Rect &r1, const GTypes::Rect &r2)
{
	return (r1.x + r1.w > r2.x
		&& r1.x  < r2.x + r2.w
		&& r1.y + r1.h > r2.y
		&& r1.y < r2.y + r2.h);
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

void PhysicsSystem::onQuadTreeSize(const Events::QuadTreeSize *evnt)
{
	m_qtSize.x = evnt->w;
	m_qtSize.y = evnt->h;
}