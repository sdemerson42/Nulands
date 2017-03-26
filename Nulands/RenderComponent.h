#pragma once

#include <string>

#include "IComponent.h"
#include "AutoList.h"
#include "SFML\Graphics.hpp"
#include "Factory.h"

class Entity;
class AnimatorSystem;
class RenderSystem;

class RenderComponent : public IComponent, public AutoList<RenderComponent>
{
	friend AnimatorSystem;
	friend RenderSystem;
public:
	RenderComponent(Entity *parent) :
		IComponent{ parent }
	{}
	RenderComponent(Entity *parent, const std::string &fName, float x, float y, float w, float h) :
		IComponent{ parent }, m_fName{ fName }, m_texCoord { x, y }, m_texSize{ w,h }
	{}
	void initialize(const std::vector<std::string> &args) override
	{
		m_fName = args[0];
		m_texCoord.x = stof(args[1]);
		m_texCoord.y = stof(args[2]);
		m_texSize.x = stof(args[3]);
		m_texSize.y = stof(args[4]);
	}
	void update() override
	{}
	const sf::Vector2f &texCoord() const
	{
		return m_texCoord;
	}
	const sf::Vector2f &texSize() const
	{
		return m_texSize;
	}
	const std::string &fName() const
	{
		return m_fName;
	}
	void outState(std::ostream &ost) const override
	{
		ost << "{ Render " << m_fName << " " << m_texCoord.x << " " << m_texCoord.y << " " << m_texSize.x << " " << m_texSize.y << " }\n";
	}
private:
	std::string m_fName;
	sf::Vector2f m_texCoord;
	sf::Vector2f m_texSize;
	static FactoryRegistry<RenderComponent> m_fReg;
};
