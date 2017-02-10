#pragma once

#include "EventBase.h"
#include <string>

namespace Events
{

	
	// Events intended for communications to and from layers

	class TextOutputEvent : public EventBase
	{
	public:
		TextOutputEvent(const std::string& text) :
			m_text{ text }
		{}
		const std::string& text() const
		{
			return m_text;
		}
	private:
		std::string m_text;
	};

	class PlayerCommandEvent : public EventBase
	{
	public:
		PlayerCommandEvent(const std::string& cmd) :
			m_cmd{ cmd }
		{}
		const std::string& cmd() const
		{
			return m_cmd;
		}
	private:
		std::string m_cmd;
	};

};
