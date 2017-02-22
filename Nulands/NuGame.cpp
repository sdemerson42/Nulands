#include "NuGame.h"

#include "RenderSystem.h"
#include "PhysicsSystem.h"

#include "RenderComponent.h"
#include "PhysicsComponent.h"

#include "Entity.h"
#include "SFML\System.hpp"

#include <iostream>

NuGame::NuGame() :
	m_window{ sf::VideoMode{800,600}, "NuGame" }
{
	m_systemVec.push_back(std::make_shared<RenderSystem>(&m_window));
	m_fixedSystemVec.push_back(std::make_shared<PhysicsSystem>());

	m_clock.restart();
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
			for (auto &fsps : m_fixedSystemVec)
				fsps->update();
		}

		for (auto &sps : m_systemVec)
			sps->update();
	}
}