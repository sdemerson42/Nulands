#pragma once

#include "ISystem.h"
#include "Events.h"
#include <memory>
#include <vector>

class Entity;
class ParticleComponent;

class ParticleSystem : public ISystem
{
public:
	void update() override;
private:
	struct Particle
	{
		int lifetime;
		int lifeCounter{ 0 };
		std::shared_ptr<Entity> entity;
		float mx;
		float my;
		ParticleSystem *system;
		void update();
	};
	std::vector<shared_ptr<Particle>> m_particle;
	void destroyParticle();
	void spawnParticle(ParticleComponent *pc);
	std::vector<Particle *> m_destroyVec;
};