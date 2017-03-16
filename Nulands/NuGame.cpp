#include "NuGame.h"
#include "NuScene.h"

#include "RenderSystem.h"
#include "PhysicsSystem.h"
#include "AnimatorSystem.h"
#include "CameraSystem.h"
#include "InputSystem.h"
#include "ParticleSystem.h"
#include "SpawnSystem.h"

#include "Entity.h"
#include "EventManager.h"

#include <fstream>
#include <string>

NuGame::NuGame(unsigned int winW, unsigned int winH) :
	m_window{ sf::VideoMode{ winW, winH }, "NuGame" }, m_sceneIndex{ -1 }
{
	m_fixedSystem.push_back(std::make_shared<InputSystem>());
	m_system.push_back(std::make_shared<RenderSystem>(&m_window));

	m_fixedSystem.push_back(std::make_shared<PhysicsSystem>());
	m_fixedSystem.push_back(std::make_shared<AnimatorSystem>());
	m_fixedSystem.push_back(std::make_shared<CameraSystem>());
	m_fixedSystem.push_back(std::make_shared<ParticleSystem>());

	m_fixedSystem.push_back(std::make_shared<SpawnSystem>());

	makeScenes();

	selectScene(0);
}

void NuGame::makeScenes()
{
	std::ifstream ifs{ "Data\\Manifest.txt" };
	while (ifs)
	{
		std::string fName;
		if (!(ifs >> fName)) break;
		m_scene.push_back(std::make_shared<NuScene>(fName));
	}
}

void NuGame::update()
{
	while (m_window.isOpen())
	{

		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_window.close();
		}

		if (m_clock.getElapsedTime().asSeconds() + m_deltaTime >= 1.0f / m_frameRate)
		{
			m_deltaTime = m_clock.getElapsedTime().asSeconds() + m_deltaTime - (1.0f / m_frameRate);
			m_clock.restart();
			for (auto &fsps : m_fixedSystem)
				fsps->update();
		}

		for (auto &sps : m_system)
			sps->update();
	}
}

void NuGame::selectScene(int scene)
{
	if (m_sceneIndex != -1)
		m_scene[m_sceneIndex]->close();

	m_sceneIndex = scene;
	m_scene[m_sceneIndex]->initialize(m_persistentEntity);
}