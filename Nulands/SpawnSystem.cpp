#include "SpawnSystem.h"

void SpawnSystem::onSpawnEvent(const Events::SpawnEvent *evnt)
{
	m_spawnEvent.push_back(*evnt);
}

void SpawnSystem::update()
{
	for (auto e : m_spawnEvent)
	{
		Events::Instantiate inst;
		inst.spawn = e;
		eventManager.broadcast(&inst);
	}

	m_spawnEvent.clear();
}