#pragma once

#include "IComponent.h"
#include "AutoList.h"
#include "GTypes.h"
#include "SFML\Graphics.hpp"

class PhysicsComponent : public IComponent, public AutoList<PhysicsComponent>
{
public:
	PhysicsComponent(Entity *parent, float px, float py, float w, float h, bool usesGravity = false, bool solid = false) :
		IComponent{ parent }, m_collisionBox{ px, py, w, h }, m_usesGravity{ usesGravity }, m_solid{ solid }
	{}
	void update() override
	{}
	const GTypes::Rect &collisionBox() const
	{
		return m_collisionBox;
	}
	bool usesGravity() const
	{
		return m_usesGravity;
	}
	bool solid() const
	{
		return m_solid;
	}
	void setMomentum(float x, float y)
	{
		m_momentum.x = x;
		m_momentum.y = y;
	}
	const sf::Vector2f &momentum() const
	{
		return m_momentum;
	}
private:
	GTypes::Rect m_collisionBox;
	bool m_usesGravity{ false };
	bool m_solid{ false };
	sf::Vector2f m_momentum{ 0,0 };
};
