#pragma once

#include "ISystem.h"
#include "GTypes.h"
#include "Events.h"

class PhysicsComponent;
class QuadTree;

class PhysicsSystem : public ISystem
{
public:
	PhysicsSystem()
	{
		eventManager.registerFunc(this, &PhysicsSystem::onQuadTreeSize);
	}
	~PhysicsSystem()
	{
		eventManager.unregisterListener(this);
	}
	void update() override;
private:
	const float m_gravity = 0.1f;
	const float m_maxVelocity = 10.0f;
	const float m_drag = 0.1f;
	bool m_dragFlag;
	QuadTree *m_qt;
	sf::Vector2f m_qtSize{ 0,0 };
	void adjustForces(PhysicsComponent *);
	void applyGravity(PhysicsComponent *);
	bool collisionX(PhysicsComponent *, PhysicsComponent *, float);
	bool collisionY(PhysicsComponent *, PhysicsComponent *, float);
	bool collide(const GTypes::Rect &, const GTypes::Rect &);
	void applyForce(PhysicsComponent *, float, float);
	float constrainToMax(float);
	void checkCollisions();
	void onQuadTreeSize(const Events::QuadTreeSize *evnt);
};

