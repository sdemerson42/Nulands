#pragma once

#include "EventManager.h"

class ILayer: public EventHandler
{
public:
	virtual ~ILayer()
	{}
	virtual void update() = 0;
	explicit operator bool() const
	{
		return m_state;
	}
protected:
	void setLayerState(bool state)
	{
		m_state = state;
	}
private:
	bool m_state = true;
};

