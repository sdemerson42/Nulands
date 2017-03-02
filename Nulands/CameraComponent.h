#pragma once

#include "IComponent.h"
#include "AutoList.h"
#include "SFML\Graphics.hpp"
#include "GTypes.h"

class CameraSystem;
class Entity;

class CameraComponent : public IComponent, public AutoList<CameraComponent>
{
public:
	friend CameraSystem;
	CameraComponent(Entity *parent, float vx, float vy, float vw, float vh,
		float vpx, float vpy, float vpxr, float vpyr, float x, float y, float w, float h, float lb, float rb, float tb, float bb);
	void update() override
	{}
private:
	GTypes::Rect m_collisionBox;
	float m_leftBound;
	float m_rightBound;
	float m_topBound;
	float m_bottomBound;
	sf::Vector2f m_lastPosition;
	sf::Vector2f m_currentPosition;
	sf::View m_view;
};
