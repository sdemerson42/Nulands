#pragma once

#include <map>
#include <string>
#include <vector>

#include "ISystem.h"
#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"

class RenderSystem: public ISystem
{
public:
	RenderSystem(sf::RenderWindow *windowRef) :
		m_windowRef{ windowRef }
	{}
	void update() override;
private:
	sf::RenderWindow *m_windowRef;
	std::map<std::string, sf::VertexArray> m_vaMap;
	std::map<std::string, sf::Texture> m_textureMap;
	std::vector<std::string> m_textureOrder;
	void fillVas();
	void drawVas();
};
