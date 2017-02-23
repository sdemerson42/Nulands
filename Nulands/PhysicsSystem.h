#pragma once

#include "ISystem.h"
#include "GTypes.h"

class PhysicsComponent;
class QuadTree;

class PhysicsSystem : public ISystem
{
public:
	void update() override;
private:
	const float m_gravity = 0.1f;
	const float m_maxVelocity = 10.0f;
	QuadTree *m_qt;
	void adjustForces(PhysicsComponent *);
	void applyGravity(PhysicsComponent *);
	bool collisionX(PhysicsComponent *, PhysicsComponent *, float);
	bool collisionY(PhysicsComponent *, PhysicsComponent *, float);
	bool collide(const GTypes::Rect &, const GTypes::Rect &);
	void applyForce(PhysicsComponent *, float, float);
	float constrainToMax(float);
	void checkCollisions();
};

