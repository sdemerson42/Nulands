#include "NuScene.h"

#include "RenderComponent.h"
#include "PhysicsComponent.h"
#include "AnimatorComponent.h"
#include "TilesComponent.h"
#include "CameraComponent.h"
#include "PlayerInputComponent.h"
#include "ParticleComponent.h"

#include "Factory.h"
#include "Events.h"
#include "Entity.h"
#include "SFML\System.hpp"


NuScene::NuScene(const std::string &fName) :
	m_dataFName{ fName }
{
	m_factory = make_shared<Factory>();
	m_factory->createBlueprints("Blueprints.txt");
	Events::QuadTreeSize qt{ 800, 600 };
	eventManager.broadcast(&qt);
}

void NuScene::initialize(std::vector<std::shared_ptr<Entity>> &persistentVec, bool fromState)
{
	if (fromState)
		initFromState();
	else
		initFromFile(persistentVec);
}

void NuScene::initFromFile(std::vector<std::shared_ptr<Entity>> &persistentVec)
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

		if (name[0] == '!')
		{
			name.erase(name.begin());
			m_factory->createEntity(persistentVec, name, x, y);
		}
		else
			m_factory->createEntity(m_entityVec, name, x, y);
	}
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