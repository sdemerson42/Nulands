#include "ParticleSystem.h"
#include "RenderComponent.h"
#include "ParticleComponent.h"
#include "Entity.h"
#include <algorithm>

void ParticleSystem::Particle::update()
{
	entity->addPosition(mx, my);
	++lifeCounter;
	if (lifeCounter == lifetime)
		system->m_destroyVec.push_back(this);
}

void ParticleSystem::update()
{
	for (int i = 0; i < AutoList<ParticleComponent>::size(); ++i)
	{
		auto pc = AutoList<ParticleComponent>::get(i);
		if (pc->active()) spawnParticle(pc);
	}

	for (auto &sp : m_particle)
		sp->update();

	destroyParticle();
}

void ParticleSystem::destroyParticle()
{
	for (auto p : m_destroyVec)
	{
		auto pi = std::find_if(m_particle.begin(), m_particle.end(), [p](std::shared_ptr<Particle> &spp)
		{
			return spp.get() == p;
		});
		if (pi != m_particle.end())
			m_particle.erase(pi);
	}
	m_destroyVec.clear();
}

void ParticleSystem::spawnParticle(ParticleComponent *pc)
{
	pc->m_spawnCounter += pc->m_spawnRate;
	int pTot = pc->m_spawnCounter;
	pc->m_spawnCounter -= (float) pTot;

	int pCounter = 0;
	while (pCounter < pTot)
	{
		m_particle.push_back(std::make_shared<Particle>());
		auto particle = m_particle[m_particle.size() - 1].get();
		particle->entity = std::make_shared<Entity>();
		particle->entity->setPosition(pc->m_origin.x + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / pc->m_origin.w)),
			pc->m_origin.y + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / pc->m_origin.y)));
		particle->entity->addComponent<RenderComponent>(particle->entity.get(), pc->m_renderData.fName, pc->m_renderData.texPosition.x,
			pc->m_renderData.texPosition.y, pc->m_renderData.texPosition.w, pc->m_renderData.texPosition.h);
		particle->lifetime = pc->m_lifetime;
		particle->system = this;

		if (pc->m_emitPattern == ParticleComponent::EmitPattern::Directional)
		{
			sf::Vector2f tv{ pc->m_travelVector };
			float m = sqrt(pow(tv.x, 2) + pow(tv.y, 2));
			float speed = pc->m_speed + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / pc->m_speedVariance));
			tv.x = (tv.x / m) * speed;
			tv.y = (tv.y / m) * speed;
			particle->mx = tv.x;
			particle->my = tv.y;
		}

		++pCounter;
	}
	
}
