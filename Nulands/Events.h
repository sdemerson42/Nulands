#pragma once

#include "EventBase.h"
#include "SFML\Graphics.hpp"

namespace Events
{

	// Intra-System Events

	class CameraMovementEvent : public EventBase
	{
	public:
		CameraMovementEvent(sf::View *viewRef) :
			m_viewRef{ viewRef }
		{}
		sf::View *viewRef() const
		{
			return m_viewRef;
		}
	private:
		sf::View *m_viewRef;
	};

};
