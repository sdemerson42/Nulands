#include "DespawnSystem.h"

void DespawnSystem::update()
{
	for (auto &e : m_despawnEvent)
	{
		Events::Destroy d;
		d.despawn = e;
		eventManager.broadcast(&d);
	}
	m_despawnEvent.clear();
}

void DespawnSystem::onDespawnEvent(const Events::DespawnEvent *evnt)
{
	m_despawnEvent.push_back(*evnt);
}