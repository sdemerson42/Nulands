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

	// System Events

	struct QuadTreeSize : public EventBase
	{
		QuadTreeSize(float _w, float _h) :
			w{ _w }, h{ _h }
		{}
		float w;
		float h;
	};

	


};
