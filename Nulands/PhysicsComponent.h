#pragma once

#include "IComponent.h"
#include "AutoList.h"
#include "GTypes.h"
#include "SFML\Graphics.hpp"
#include "Factory.h"

class PhysicsSystem;

class PhysicsComponent : public IComponent, public AutoList<PhysicsComponent>
{
public:
	friend PhysicsSystem;

	PhysicsComponent(Entity *parent) :
		IComponent{ parent }
	{}
	PhysicsComponent(Entity *parent, float x, float y, float w, float h, bool gravity, bool solid, bool isStatic, float mx = 0.0f, float my = 0.0f) :
		IComponent{ parent }, m_collisionBox{ x,y,w,h }, m_usesGravity{ gravity }, m_solid{ solid }, m_static{ isStatic }, m_momentum{ mx, my }
	{}
	void initialize(const std::vector<std::string> &args) override
	{
		m_collisionBox.x = stof(args[0]);
		m_collisionBox.y = stof(args[1]);
		m_collisionBox.w = stof(args[2]);
		m_collisionBox.h = stof(args[3]);
		m_usesGravity = (args[4] == "true" ? true : false);
		m_solid = (args[5] == "true" ? true : false);
		m_static = (args[6] == "true" ? true : false);
		m_momentum.x = stof(args[7]);
		m_momentum.y = stof(args[8]);
	}
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
	void outState(std::ostream &ost) const override
	{
		ost << "{ Physics " << " " << m_collisionBox.x << " " << m_collisionBox.y << " " << m_collisionBox.w << " " << m_collisionBox.h << " " <<
			(m_usesGravity ? "true" : "false") << " " << (m_solid ? "true" : "false") << " " << (m_static ? "true" : "false") <<  " " <<
			m_momentum.x << " " << m_momentum.y << " }\n";
	}
private:
	GTypes::Rect m_collisionBox;
	bool m_usesGravity{ false };
	bool m_solid{ false };
	bool m_static{ false };
	sf::Vector2f m_momentum;
	static FactoryRegistry<PhysicsComponent> m_fReg;
};
