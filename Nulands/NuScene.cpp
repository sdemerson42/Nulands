#include "NuScene.h"

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

NuScene::NuScene(const std::string &fName) :
	m_dataFName{ fName }
{
	m_factory = make_shared<Factory>();
	m_factory->createBlueprints("Blueprints.txt");
}

void NuScene::initialize()
{
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
}

void NuScene::close()
{
	// Persistent data needs to be handled

	m_entityVec.clear();
}