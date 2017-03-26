#pragma once

#include "IComponent.h"
#include "GTypes.h"
#include <string>
#include "SFML\Graphics.hpp"
#include "Factory.h"

class ParticleSystem;

class ParticleComponent : public IComponent, public AutoList<ParticleComponent>
{
public:
	friend class ParticleSystem;
	enum class EmitPattern
	{
		Directional
	};
	ParticleComponent(Entity *parent) :
		IComponent{ parent }
	{}
	void initialize(const std::vector<std::string> &args) override
	{
		m_origin.x = stof(args[0]);
		m_origin.y = stof(args[1]);
		m_origin.w = stof(args[2]);
		m_origin.h = stof(args[3]);
		m_emitPattern = EmitPattern::Directional;
		m_lifetime = stoi(args[5]);
		m_speed = stof(args[6]);
		m_spawnRate = stof(args[7]);
		m_angleVariance = stof(args[8]);
		m_speedVariance = stof(args[9]);
		m_renderData.fName = args[10];
		m_renderData.texPosition.x = stof(args[11]);
		m_renderData.texPosition.y = stof(args[12]);
		m_renderData.texPosition.w = stof(args[13]);
		m_renderData.texPosition.h = stof(args[14]);
		m_travelVector.x = stof(args[15]);
		m_travelVector.y = stof(args[16]);
	}
	void update() override
	{}
	void outState(std::ostream &ost) const override
	{
		ost << "{ Particle " << m_origin.x << " " << m_origin.y << " " << m_origin.w << " " << m_origin.h << " " << "TEMP " << m_lifetime << " " << m_speed << " " <<
			m_spawnRate << " " << m_angleVariance << " " << m_speedVariance << " " << m_renderData.fName << " " << m_renderData.texPosition.x << " " <<
			m_renderData.texPosition.y << " " << m_renderData.texPosition.w << " " << m_renderData.texPosition.h << " " << m_travelVector.x << " " <<
			m_travelVector.y << " }\n";
	}
private:
	GTypes::Rect m_origin;
	EmitPattern m_emitPattern;
	int m_lifetime;
	float m_speed;
	float m_spawnRate;
	struct RenderData
	{
		RenderData()
		{}
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

	struct Particle
	{
		Particle(ParticleComponent *_parent) :
			parent{ _parent }
		{}
		~Particle()
		{
			entity.reset();
		}
		ParticleComponent *parent;
		int lifetime;
		int lifeCounter{ 0 };
		std::shared_ptr<Entity> entity;
		float mx;
		float my;
		void update();
	};
	std::vector<shared_ptr<Particle>> m_particle;
	std::vector<Particle *> m_destroyVec;
	static FactoryRegistry<ParticleComponent> m_fReg;
};