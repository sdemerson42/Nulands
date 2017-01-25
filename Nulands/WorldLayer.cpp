#include "WorldLayer.h"

void WorldLayer::onPlayerCommand(const Events::PlayerCommandEvent* evnt)
{
	// Test Code
	std::string s;
	s += "WorldLayer has received a command: ";
	s += evnt->cmd();
	Events::TextOutputEvent toe{ s };
	broadcast(&toe);
}