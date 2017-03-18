#include "BehaviorSystem.h"
#include "BehaviorComponent.h"

void BehaviorSystem::update()
{
	for (int i = 0; i < AutoList<BehaviorComponent>::size(); ++i)
	{
		auto b = AutoList<BehaviorComponent>::get(i);
		b->update();
	}
}