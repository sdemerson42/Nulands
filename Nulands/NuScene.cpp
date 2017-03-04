#include "NuScene.h"

#include "RenderSystem.h"
#include "PhysicsSystem.h"
#include "AnimatorSystem.h"
#include "CameraSystem.h"
#include "InputSystem.h"
#include "ParticleSystem.h"

#include "RenderComponent.h"
#include "PhysicsComponent.h"
#include "AnimatorComponent.h"
#include "TilesComponent.h"
#include "CameraComponent.h"
#include "PlayerInputComponent.h"
#include "ParticleComponent.h"

#include "Factory.h"

#include "Entity.h"
#include "SFML\System.hpp"

#include <iostream>

NuScene::NuScene() :
	m_window{ sf::VideoMode{800, 600}, "NuGame" }
{
	m_systemVec.push_back(std::make_shared<RenderSystem>(&m_window));

	m_fixedSystemVec.push_back(std::make_shared<InputSystem>());
	m_fixedSystemVec.push_back(std::make_shared<PhysicsSystem>());
	m_fixedSystemVec.push_back(std::make_shared<AnimatorSystem>());
	m_fixedSystemVec.push_back(std::make_shared<CameraSystem>());
	m_fixedSystemVec.push_back(std::make_shared<ParticleSystem>());

	m_factory = make_shared<Factory>();

	m_factory->createBlueprints("Blueprints.txt");

	// Test data

	for (int j = 0; j < 20; ++j)
	{
		for (int i = 0; i < 20; ++i)
		{
			m_factory->createEntity(m_entityVec, "Bak", i * 32, j * 32);
		}
	}
	m_factory->createEntity(m_entityVec, "Map");
	m_factory->createEntity(m_entityVec, "Player", 60, 0);
	auto p = m_entityVec[m_entityVec.size() - 1].get();
	p->addComponent<PlayerInputComponent>(p);


	m_factory->createEntity(m_entityVec, "Snow");
	
	
	// End test data

	m_clock.restart();
}

void NuScene::update()
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