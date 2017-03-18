#pragma once

#include "ISystem.h"

class BehaviorSystem : public ISystem
{
public:
	void update() override;
};