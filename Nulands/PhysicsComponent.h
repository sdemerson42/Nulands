#pragma once

#include "IComponent.h"
#include "AutoList.h"
#include "GTypes.h"
#include "SFML\Graphics.hpp"

class PhysicsComponent : public IComponent, public AutoList<PhysicsComponent>
{
public:
	PhysicsComponent(Entity *parent, float px, float py, float w, float h, bool usesGravity = false, bool solid = false, bool isStatic = false) :
		IComponent{ parent }, m_collisionBox{ px, py, w, h }, m_usesGravity{ usesGravity }, m_solid{ solid }, m_static{ isStatic }
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
	bool isStatic() const
	{
		return m_static;
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
	bool m_static{ false };
	sf::Vector2f m_momentum{ 0,0 };
};
