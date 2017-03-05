#pragma once

#include <vector>
#include <memory>
#include "SFML\Graphics.hpp"

class ISystem;
class NuScene;

class NuGame
{
public:
	NuGame(unsigned int winW, unsigned int winH);
	void update();
	void makeScenes();
	void selectScene(int scene);
private:
	std::vector<std::shared_ptr<ISystem>> m_system;
	std::vector<std::shared_ptr<ISystem>> m_fixedSystem;
	sf::RenderWindow m_window;
	sf::Clock m_clock;
	float m_deltaTime{ 0.0f };
	const float m_frameRate{ 60.0f };
	std::vector<std::shared_ptr<NuScene>> m_scene;
	int m_sceneIndex;
};
