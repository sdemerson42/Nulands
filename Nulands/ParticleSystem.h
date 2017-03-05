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
	void destroyParticle(ParticleComponent *pc);
	void spawnParticle(ParticleComponent *pc);
};