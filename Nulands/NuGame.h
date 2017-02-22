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
	std::vector<std::shared_ptr<ISystem>> m_fixedSystemVec;
	sf::RenderWindow m_window;
	sf::Clock m_clock;
	float m_deltaTime{ 0.0f };
	const float m_frameRate{ 60.0f };
};