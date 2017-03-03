#include "NuScene.h"

#include "RenderSystem.h"
#include "PhysicsSystem.h"
#include "AnimatorSystem.h"
#include "CameraSystem.h"
#include "InputSystem.h"

#include "RenderComponent.h"
#include "PhysicsComponent.h"
#include "AnimatorComponent.h"
#include "TilesComponent.h"
#include "CameraComponent.h"
#include "PlayerInputComponent.h"

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

	m_factory = make_shared<Factory>();

	m_factory->createBlueprints("Blueprints.txt");

	// Test data

	for (int j = 0; j < 20; ++j)
	{
		for (int i = 0; i < 20; ++i)
		{
			m_entityVec.push_back(std::make_shared<Entity>());
			auto p = m_entityVec[m_entityVec.size() - 1].get();
			p->addComponent<RenderComponent>(p, "Squares.png", 64, 0, 32, 32);
			p->setPosition(i * 32, j * 32);
		}
	}

	m_entityVec.push_back(std::make_shared<Entity>());
	auto p = m_entityVec[m_entityVec.size() - 1].get();
	p->addComponent<TilesComponent>(p, "Tileset.txt");

	m_entityVec.push_back(std::make_shared<Entity>());
	p = m_entityVec[m_entityVec.size() - 1].get();
	p->addComponent<RenderComponent>(p, "Player.png", 0, 0, 32, 32);
	p->addComponent<PhysicsComponent>(p, 2, 2, 28, 28, true, true, false);
	p->getComponent<PhysicsComponent>()->setMomentum(4, 0);
	p->addComponent<AnimatorComponent>(p);
	p->getComponent<AnimatorComponent>()->addAnimation(AnimatorComponent::Animation{ "right", std::vector<float>{32,0,32,32,64,0,32,32,96,0,32,32,64,0,32,32}, 10 });
	p->getComponent<AnimatorComponent>()->addAnimation(AnimatorComponent::Animation{ "left", std::vector<float>{128,0,32,32,160,0,32,32,192,0,32,32,160,0,32,32}, 10 });
	p->getComponent<AnimatorComponent>()->addAnimation(AnimatorComponent::Animation{ "idleright", std::vector<float>{0, 0, 32, 32}, 1, false });
	p->getComponent<AnimatorComponent>()->addAnimation(AnimatorComponent::Animation{ "idleleft", std::vector<float>{224, 0, 32, 32}, 1, false });
	p->getComponent<AnimatorComponent>()->play("right");
	p->addComponent<CameraComponent>(p, 0, 0, 800, 600, 0, 0, 1, 1, 16, 16, 100);
	p->addComponent<PlayerInputComponent>(p);

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