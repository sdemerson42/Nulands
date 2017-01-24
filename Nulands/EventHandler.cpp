#include "EventHandler.h"

void EventHandler::handleEvent(const EventBase* evnt)
{
	auto p = m_delegateMap.find(std::type_index{ typeid(*evnt) });
	if (p != m_delegateMap.end()) p->second->call(evnt);
}

void EventHandler::broadcast(const EventBase* evnt)
{
	for (int i = 0; i < AutoList<EventHandler>::size(); ++i)
		AutoList<EventHandler>::get(i)->handleEvent(evnt);
}