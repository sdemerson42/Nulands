#include "CameraComponent.h"
#include "Entity.h"

CameraComponent::CameraComponent(Entity *parent, float vx, float vy, float vw, float vh,
	float vpx, float vpy, float vpxr, float vpyr, float x, float y, float w, float h, float lb, float rb, float tb, float bb) :
	IComponent{ parent }, m_view{ sf::FloatRect{vx, vy, vw, vh} },
	m_collisionBox{ x, y, w, h }, m_leftBound{ lb }, m_rightBound{ rb }, m_topBound{ tb }, m_bottomBound{ bb }
{
	m_currentPosition = sf::Vector2f{ parent->position().x + m_collisionBox.x, parent->position().y + m_collisionBox.y };
	m_lastPosition = m_currentPosition;
	m_view.setViewport(sf::FloatRect{ vpx, vpy, vpxr, vpyr });
}