#pragma once

#include "EventBase.h"
#include "GTypes.h"
#include "SFML\Graphics.hpp"
#include <vector>

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

	struct ProxMapSize : public EventBase
	{
		ProxMapSize(float _w, float _h, float _cw, float _ch) :
			w{ _w }, h{ _h }, cw{ _cw }, ch{ _ch }
		{}
		float w;
		float h;
		float cw;
		float ch;
	};

	struct SpawnEvent : public EventBase
	{
		std::string bName;
		float x;
		float y;
		bool persist = false;
	};

	struct Instantiate : public EventBase
	{
		SpawnEvent spawn;
	};

	struct DespawnEvent : public EventBase
	{
		GTypes::EntityGuid guid;
	};

	struct Destroy : public EventBase
	{
		DespawnEvent despawn;
	};

	// Sound System Events

	enum class SoundEventType
	{
		AddSound, AddMusic, PlaySound, PlayMusic, StopSound, StopMusic
	};

	struct SoundEvent : public EventBase
	{
		SoundEventType type;
		std::string name;
		std::string fName;
		bool loop = false;
		float volume = 100.0f;
	};

};
