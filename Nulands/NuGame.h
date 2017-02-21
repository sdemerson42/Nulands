#pragma once

#include <vector>
#include <memory>

#include "SFML\Graphics.hpp"

class Entity;
class ISystem;

class NuGame
{
public:
	NuGame();
	void update();
private:
	std::vector<std::shared_ptr<Entity>> m_entityVec;
	std::vector<std::shared_ptr<ISystem>> m_systemVec;
	sf::RenderWindow m_window;
	sf::Clock m_clock;
	float m_elapsed{ 0 };
};