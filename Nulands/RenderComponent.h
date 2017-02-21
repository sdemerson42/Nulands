#pragma once

#include <string>

#include "IComponent.h"
#include "AutoList.h"
#include "SFML\Graphics.hpp"

class Entity;

class RenderComponent : public IComponent, public AutoList<RenderComponent>
{
public:
	RenderComponent(Entity *parent, const std::string &fName, sf::Vector2f &texCoord, const sf::Vector2f &texSize) :
		IComponent{ parent }, m_fName{ fName }, m_texCoord { texCoord }, m_texSize{ texSize }
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
private:
	std::string m_fName;
	sf::Vector2f m_texCoord;
	sf::Vector2f m_texSize;
};
