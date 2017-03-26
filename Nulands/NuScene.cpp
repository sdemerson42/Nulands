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
#include <iostream>
#include <algorithm>

NuScene::NuScene(const std::string &fName) :
	m_dataFName{ fName }
{

	eventManager.registerFunc(this, &NuScene::onInstantiate);
	eventManager.registerFunc(this, &NuScene::onDestroy);

	m_factory = make_shared<Factory>();
	m_factory->createBlueprints("Blueprints.txt");
	Events::QuadTreeSize qt{ 800, 600 };
	eventManager.broadcast(&qt);
	Events::ProxMapSize ps{ 1600, 1600, 96, 96 };
	eventManager.broadcast(&ps);
	m_activeScene = false;
}

void NuScene::initialize(std::vector<std::shared_ptr<Entity>> &persistentVec)
{
	if (m_stateImage.str().length() > 0)
		initFromState();
	else
		initFromFile(persistentVec);

	m_activeScene = true;
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
	
	m_stateImage.str(std::string());
	m_stateImage.clear(ios_base::goodbit);

	for (auto &sp : m_entityVec)
		sp->outState(m_stateImage);
	m_entityVec.clear();
	m_activeScene = false;
}

void NuScene::onInstantiate(const Events::Instantiate *evnt)
{
	if (m_activeScene)
	{
		m_factory->createEntity(m_entityVec, evnt->spawn);
	}
}

void NuScene::onDestroy(const Events::Destroy *evnt)
{
	if (m_activeScene)
	{
		GTypes::EntityGuid guid = evnt->despawn.guid;
		auto i = std::find_if(m_entityVec.begin(), m_entityVec.end(), [guid](std::shared_ptr<Entity> &sp) {
			return sp->guid() == guid;
		});
		if (i != m_entityVec.end())
			m_entityVec.erase(i);
	}
}
