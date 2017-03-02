#include "CameraSystem.h"
#include "CameraComponent.h"
#include "Entity.h"

void CameraSystem::update()
{
	// NOTE: For now, camera movement depends on a single focus. Change this later.

	if (AutoList<CameraComponent>::size() == 0) return;
	auto c = AutoList<CameraComponent>::get(0);
	auto p = c->getParent();

	float x = p->position().x + c->m_offset.x;
	float y = p->position().y + c->m_offset.y;
	float cx = c->m_view.getCenter().x;
	float cy = c->m_view.getCenter().y;

	float pDist = sqrt(pow(x - cx, 2) + pow(y - cy, 2));
	
	if (pDist > c->m_trackDistance)
	{
		float m = pDist - c->m_trackDistance;
		sf::Vector2f v{ m * ((x - cx) / pDist), m * ((y - cy) / pDist) };
		c->m_view.move(v);
	}

}