#include "AnimatorSystem.h"
#include "AnimatorComponent.h"
#include "RenderComponent.h"
#include "Entity.h"

void AnimatorSystem::update()
{
	for (int i = 0; i < AutoList<AnimatorComponent>::size(); ++i)
	{
		AnimatorComponent *p = AutoList<AnimatorComponent>::get(i);
		if (p->active() && p->m_animating)
		{
			auto a = p->m_animIndex;
			if (a != p->m_animation.end())
			{
				++p->m_counter;
				if (p->m_counter == a->speed)
				{
					p->m_counter = 0;
					++p->m_frameIndex;
					if (p->m_frameIndex == a->frame.size())
					{
						if (!a->loop)
						{
							p->m_animating = false;
						}
						else
						{
							p->m_frameIndex = 0;
						}
					}
					if (p->m_animating)
					{
						auto r = p->getParent()->getComponent<RenderComponent>();
						if (r != nullptr)
						{
							r->m_texCoord = sf::Vector2f{ a->frame[p->m_frameIndex].x, a->frame[p->m_frameIndex].y };
							r->m_texSize = sf::Vector2f{ a->frame[p->m_frameIndex].w, a->frame[p->m_frameIndex].h };
						}
					}
				}
			}
		}
	}
}