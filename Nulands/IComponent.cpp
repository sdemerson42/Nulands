#include "IComponent.h"
#include <iostream>

std::ostream &operator << (std::ostream &ost, const IComponent &c)
{
	c.outState(ost);
	return ost;
}