#pragma once

#include "IComponent.h"
#include "GTypes.h"
#include <string>
#include "SFML\Graphics.hpp"

class ParticleSystem;

class ParticleComponent : public IComponent, public AutoList<ParticleComponent>
{
public:
	friend class ParticleSystem;
	enum class EmitPattern
	{
		Directional
	};
	ParticleComponent(Entity *parent, float ox, float oy, float ow, float oh, EmitPattern emitPattern, int lifetime, float speed, float spawnRate, float angleVariance,
		float speedVariance, const std::string &fName, float tx, float ty, float tw, float th, float travelX = 0, float travelY = 0) :
		IComponent{ parent }, m_origin{ ox, oy, ow, oh }, m_emitPattern{ emitPattern }, m_lifetime{ lifetime }, m_speed{ speed }, m_spawnRate{ spawnRate },
		m_angleVariance{ angleVariance }, m_speedVariance{ speedVariance }, m_renderData{ fName, tx, ty, tw, th }, m_travelVector{ travelX, travelY }
	{}
	void update() override
	{}
private:
	GTypes::Rect m_origin;
	EmitPattern m_emitPattern;
	int m_lifetime;
	float m_speed;
	float m_spawnRate;
	struct RenderData
	{
		RenderData(const std::string &_fName, float tx, float ty, float tw, float th) :
			fName{ _fName }, texPosition{ tx, ty, tw, th }
		{}
		std::string fName;
		GTypes::Rect texPosition;
	};
	RenderData m_renderData;
	float m_angleVariance;
	float m_speedVariance;
	sf::Vector2f m_travelVector;
	float m_spawnCounter{ 0.0f };
};