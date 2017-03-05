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


NuScene::NuScene(const std::string &fName) :
	m_dataFName{ fName }
{
	m_factory = make_shared<Factory>();
	m_factory->createBlueprints("Blueprints.txt");
}

void NuScene::initialize(bool fromState)
{
	if (fromState)
		initFromState();
	else
		initFromFile();
}

void NuScene::initFromFile()
{
	std::ifstream ifs{ "Data\\" + m_dataFName };
	while (ifs)
	{
		std::string name;
		
		if (!(ifs >> name))
		{
			ifs.clear(ios_base::failbit);
			break;
		}

		float x, y;
		ifs >> x >> y;

		m_factory->createEntity(m_entityVec, name, x, y);
	}
	m_entityVec[2]->addComponent<PlayerInputComponent>(m_entityVec[2].get());
}

void NuScene::initFromState()
{
	m_factory->createEntity(m_entityVec, m_stateImage);
}

void NuScene::close()
{
	// Persistent data needs to be handled

	// Test

	for (auto &sp : m_entityVec)
		sp->outState(m_stateImage);

	m_entityVec.clear();
}