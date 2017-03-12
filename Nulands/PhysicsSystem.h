#pragma once

#include "ISystem.h"
#include "GTypes.h"
#include "Events.h"
#include <memory>
#include "QuadTree.h"
#include "ProxMap.h"

class PhysicsComponent;

class PhysicsSystem : public ISystem
{
public:
	PhysicsSystem();
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
	std::unique_ptr<QuadTree> m_qt;
	std::unique_ptr<ProxMap> m_prox;
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

