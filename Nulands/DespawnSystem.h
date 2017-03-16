#pragma once

#include "ISystem.h"
#include "GTypes.h"
#include <vector>

class DespawnSystem : public ISystem
{
public:
	DespawnSystem()
	{
		eventManager.registerFunc(this, &DespawnSystem::onDespawnEvent);
	}
	~DespawnSystem()
	{
		eventManager.unregisterListener(this);
	}
	void update() override;
private:
	void onDespawnEvent(const Events::DespawnEvent *evnt);
	std::vector<Events::DespawnEvent> m_despawnEvent;
};
