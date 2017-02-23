#pragma once

#include "ISystem.h"

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
	bool collisionX(PhysicsComponent *, PhysicsComponent *);
	bool collisionY(PhysicsComponent *, PhysicsComponent *);
	bool collide(PhysicsComponent *, PhysicsComponent *);
	void applyForce(PhysicsComponent *, float, float);
	float constrainToMax(float);
	void checkCollisions();
	float m_curXm;
	float m_curYm;
};

