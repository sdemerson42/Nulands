#include "CameraComponent.h"

FactoryRegistry<CameraComponent> CameraComponent::m_fReg{ "Camera" };

void CameraComponent::initialize(const std::vector<std::string> &args)
{
	m_vPosition.x = stof(args[0]);
	m_vPosition.y = stof(args[1]);

	m_view.reset(sf::FloatRect{ m_vPosition.x, m_vPosition.y, stof(args[2]), stof(args[3]) });
	m_view.setViewport(sf::FloatRect{ stof(args[4]), stof(args[5]), stof(args[6]), stof(args[7]) });
	
	m_offset.x = stof(args[8]);
	m_offset.y = stof(args[9]);
	m_trackDistance = stof(args[10]);
}