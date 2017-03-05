#pragma once

#include <string>

#include "IComponent.h"
#include "AutoList.h"
#include "SFML\Graphics.hpp"

class Entity;
class AnimatorSystem;
class RenderSystem;

class RenderComponent : public IComponent, public AutoList<RenderComponent>
{
	friend AnimatorSystem;
	friend RenderSystem;
public:
	RenderComponent(Entity *parent, const std::string &fName, sf::Vector2f &texCoord, const sf::Vector2f &texSize) :
		IComponent{ parent }, m_fName{ fName }, m_texCoord { texCoord }, m_texSize{ texSize }
	{}
	RenderComponent(Entity *parent, const std::string &fName, float x, float y, float w, float h) :
		IComponent{ parent }, m_fName{ fName }, m_texCoord{ x,y }, m_texSize{ w,h }
	{}
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
};
