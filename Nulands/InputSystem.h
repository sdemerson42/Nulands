#pragma once

#include "ISystem.h"
#include "SFML\Graphics.hpp"

class InputSystem : public ISystem
{
public:
	void update() override;
};