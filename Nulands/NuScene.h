#pragma once

#include <vector>
#include <memory>

#include "SFML\Graphics.hpp"

class Entity;
class ISystem;
class Factory;

class NuScene
{
public:
	NuScene();
	void update();
private:
	std::vector<std::shared_ptr<Entity>> m_entityVec;
	std::vector<std::shared_ptr<ISystem>> m_systemVec;
	std::vector<std::shared_ptr<ISystem>> m_fixedSystemVec;
	std::shared_ptr<Factory> m_factory;
	sf::RenderWindow m_window;
	sf::Clock m_clock;
	float m_deltaTime{ 0.0f };
	const float m_frameRate{ 60.0f };
};