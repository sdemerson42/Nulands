#pragma once

#include "EventBase.h"

namespace Events
{

	class IntEvent : public EventBase
	{
	public:
		IntEvent(int val) :
			m_val{ val }
		{}
		int val() const
		{
			return m_val;
		}
	private:
		int m_val;
	};


};
