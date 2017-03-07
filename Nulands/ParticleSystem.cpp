#include "ParticleSystem.h"
#include "RenderComponent.h"
#include "ParticleComponent.h"
#include "Entity.h"
#include <algorithm>



void ParticleSystem::update()
{
	for (int i = 0; i < AutoList<ParticleComponent>::size(); ++i)
	{
		auto pc = AutoList<ParticleComponent>::get(i);
		if (pc->active()) spawnParticle(pc);

		for (auto &sp : pc->m_particle)
			sp->update();
		destroyParticle(pc);
	}
}

void ParticleSystem::destroyParticle(ParticleComponent *pc)
{
	for (auto p : pc->m_destroyVec)
	{
		auto pi = std::find_if(pc->m_particle.begin(), pc->m_particle.end(), [p](std::shared_ptr<ParticleComponent::Particle> &spp)
		{
			return spp.get() == p;
		});
		if (pi != pc->m_particle.end())
			pc->m_particle.erase(pi);
	}
	pc->m_destroyVec.clear();
}

void ParticleSystem::spawnParticle(ParticleComponent *pc)
{
	pc->m_spawnCounter += pc->m_spawnRate;
	int pTot = pc->m_spawnCounter;
	pc->m_spawnCounter -= (float) pTot;

	int pCounter = 0;
	while (pCounter < pTot)
	{
		pc->m_particle.push_back(std::make_shared<ParticleComponent::Particle>(pc));
		auto particle =pc->m_particle[pc->m_particle.size() - 1].get();
		particle->entity = std::make_shared<Entity>();
		particle->entity->setPosition(pc->getParent()->position().x + pc->m_origin.x + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / pc->m_origin.w)),
			pc->getParent()->position().y + pc->m_origin.y + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / pc->m_origin.y)));
		particle->entity->addComponent<RenderComponent>(particle->entity.get(), pc->m_renderData.fName, pc->m_renderData.texPosition.x,
			pc->m_renderData.texPosition.y, pc->m_renderData.texPosition.w, pc->m_renderData.texPosition.h);
		particle->lifetime = pc->m_lifetime;

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
