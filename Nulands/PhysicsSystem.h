#pragma once

#include "ISystem.h"

class PhysicsComponent;

class PhysicsSystem : public ISystem
{
public:
	void update() override;
private:
	const float m_gravity = 0.05f;
	const float m_maxVelocity = 10.0f;
	PhysicsComponent *m_pc;

	void move();
	void applyGravity();
	void collisionX();
	void collisionY();
	void applyForce(float, float);
	float constrainToMax(float);
};

