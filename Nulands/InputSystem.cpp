#include "InputSystem.h"
#include "Events.h"

void InputSystem::update()
{
	Events::InputWrapper iw;

	iw.x = 0.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		iw.x = 1.0f;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		iw.x = -1.0f;

	Events::InputEvent ie{ &iw };
	eventManager.broadcast(&ie);
}