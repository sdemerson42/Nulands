#pragma once

#include <map>
#include <memory>
#include <typeindex>

#include "AutoList.h"
#include "EventBase.h"

template<typename T, typename EventT>
using MFunc = void (T::*)(const EventT*);

class IDelegate
{
public:
	virtual void call(const EventBase*) = 0;
};

template<typename T, typename EventT>
class Delegate : public IDelegate
{
public:
	Delegate(T* instance, MFunc<T, EventT> funcPointer) :
		m_instance{ instance }, m_funcPointer{ funcPointer }
	{}
	void call(const EventBase* evnt) override
	{
		(m_instance->*m_funcPointer)(static_cast<const EventT*>(evnt));
	}
private:
	T* m_instance;
	MFunc<T, EventT> m_funcPointer;
};

class EventHandler: public AutoList<EventHandler>
{
public:
	template<typename T, typename EventT>
	void registerFunc(T* instance, MFunc<T, EventT> funcPointer)
	{
		m_delegateMap[std::type_index{ typeid(EventT) }] = std::make_shared<Delegate<T, EventT>>(instance, funcPointer);
	}
	void handleEvent(const EventBase*);
	static void broadcast(const EventBase*);
private:
	std::map<std::type_index, std::shared_ptr<IDelegate>> m_delegateMap;
};