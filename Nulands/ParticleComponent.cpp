#include "ParticleComponent.h"
#include "Entity.h"

void ParticleComponent::Particle::update()
{
	entity->addPosition(mx, my);
	++lifeCounter;
	if (lifeCounter == lifetime)
		parent->m_destroyVec.push_back(this);
}