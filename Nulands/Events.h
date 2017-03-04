#pragma once

#include "EventBase.h"
#include "SFML\Graphics.hpp"

class Particle;

namespace Events
{

	// Input Events

	struct InputWrapper
	{
		float x;
	};

	struct InputEvent : public EventBase
	{
		InputEvent(InputWrapper *_iw) :
			iw{ _iw }
		{}
		InputWrapper *iw;
	};

	// Particle Events

	


};
