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
private:
	sf::View m_view;
	float m_trackDistance;
	sf::Vector2f m_offset;
};
