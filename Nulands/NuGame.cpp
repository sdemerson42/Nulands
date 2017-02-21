#include "NuGame.h"
#include "RenderSystem.h"
#include "RenderComponent.h"
#include "Entity.h"
#include "SFML\System.hpp"

#include <iostream>

NuGame::NuGame() :
	m_window{ sf::VideoMode{800,600}, "NuGame" }
{
	m_systemVec.push_back(std::make_shared<RenderSystem>(&m_window));
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

		for (auto &sps : m_systemVec)
			sps->update();
		
		/*
		for (auto &spe : m_entityVec)
			spe->update();
		*/
	}
}