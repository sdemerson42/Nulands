#include "CameraComponent.h"

CameraComponent::CameraComponent(Entity *parent, float vx, float vy, float vw, float vh, float vpx, float vpy, float vxr, float vyr,
	float offsetX, float offsetY, float trackDistance) :
	IComponent{ parent }, m_vPosition{ vx, vx }, m_offset { offsetX, offsetY }, m_trackDistance{ trackDistance }
{
	m_view.reset(sf::FloatRect{ vx, vy, vw, vh });
	m_view.setViewport(sf::FloatRect{ vpx, vpy, vxr, vyr });
}