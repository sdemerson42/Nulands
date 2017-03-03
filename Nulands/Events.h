#pragma once

#include "EventBase.h"
#include "SFML\Graphics.hpp"

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

	// Intra-System Events


};
