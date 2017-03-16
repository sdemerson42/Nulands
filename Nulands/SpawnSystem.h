#pragma once

#include "ISystem.h"
#include "Events.h"
#include <vector>
#include <string>

class SpawnSystem: public ISystem
{
public:
	SpawnSystem()
	{
		eventManager.registerFunc(this, &SpawnSystem::onSpawnEvent);
	}
	virtual ~SpawnSystem()
	{
		eventManager.unregisterListener(this);
	}
	void update() override;
private:
	void onSpawnEvent(const Events::SpawnEvent *evnt);
	std::vector<Events::SpawnEvent> m_spawnEvent;
};