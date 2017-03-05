#pragma once

#include "IComponent.h"
#include "AutoList.h"
#include "SFML\Graphics.hpp"
#include "GTypes.h"

class CameraSystem;
class RenderSystem;
class Entity;

class CameraComponent : public IComponent, public AutoList<CameraComponent>
{
public:
	friend CameraSystem;
	friend RenderSystem;
	CameraComponent(Entity *parent, float vx, float vy, float vw, float vh, float vpx, float vpy, float vxr, float vyr,
		float offsetX, float offsetY, float trackDistance);
	void update() override
	{}
	void outState(std::ostream &ost) const override
	{
		ost << "{ Camera " << m_vPosition.x << " " << m_vPosition.y << " " << m_view.getSize().x << " " << m_view.getSize().y << " "
			<< m_view.getViewport().left << " " << m_view.getViewport().top << " " << m_view.getViewport().width << " " << m_view.getViewport().height
			<< " " << m_offset.x << " " << m_offset.y << " " << m_trackDistance << " }\n";
	}
private:
	sf::Vector2f m_vPosition;
	sf::View m_view;
	float m_trackDistance;
	sf::Vector2f m_offset;
};
