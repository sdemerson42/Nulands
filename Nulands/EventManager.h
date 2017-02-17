#pragma once

#include <memory>
#include <map>
#include <typeindex>
#include <vector>

#include "Events.h"


using namespace std;

template<typename T, typename EventT>
using MFunc = void(T::*)(const EventT*);

class IDelegate
{
public:
	virtual void call(const EventBase*) = 0;
	virtual void* getInstance() = 0;
};

template<typename T, typename EventT>
class Delegate : public IDelegate
{
public:
	Delegate(T* instance, MFunc<T, EventT> func) :
		m_instance{ instance }, m_func{ func }
	{}
	void call(const EventBase* evnt) override
	{
		(m_instance->*m_func)(static_cast<const EventT*>(evnt));
	}
	void* getInstance() override
	{
		return m_instance;
	}
private:
	T* m_instance;
	MFunc<T, EventT> m_func;
};

class EventHandler
{
public:
	virtual ~EventHandler()
	{}
};

class EventManager
{
public:
	template<typename T, typename EventT>
	void registerFunc(T* instance, MFunc<T, EventT> func)
	{
		if (!(dynamic_cast<EventHandler*>(instance))) return;
		auto p = m_dMap.find(type_index(typeid(EventT)));
		if (p == m_dMap.end())
		{
			m_dMap[type_index(typeid(EventT))] = vector<shared_ptr<IDelegate>>();
			p = m_dMap.find(type_index(typeid(EventT)));
		}
		p->second.push_back(make_shared<Delegate<T, EventT>>(instance, func));

		// Update manifest for cleaning later

		auto q = m_manifest.find(type_index(typeid(T)));
		if (q == m_manifest.end())
		{
			m_manifest[type_index(typeid(T))] = vector<type_index>();
			q = m_manifest.find(type_index(typeid(T)));
		}
		q->second.push_back(type_index(typeid(EventT)));
	}
	void broadcast(const EventBase* evnt)
	{
		auto p = m_dMap.find(type_index(typeid(*evnt)));
		if (p != m_dMap.end())
		{
			for (auto &sp : p->second)
			{
				sp->call(evnt);
			}
		}
	}
	template<typename T>
	void unregisterListener(T* p)
	{
		auto v = m_manifest.find(type_index(typeid(T)));
		if (v == m_manifest.end()) return;
		for (auto& ti : v->second)
		{
			auto pp = m_dMap.find(ti);
			if (pp != m_dMap.end())
			{
				for (int index = 0; index<pp->second.size(); ++index)
				{
					auto sp = pp->second[index];
					if (static_cast<T*>(sp->getInstance()) == p)
					{
						pp->second.erase(pp->second.begin() + index);
						--index;
					}
				}
			}
		}
	}
private:
	static map<type_index, vector<shared_ptr<IDelegate>>> m_dMap;
	static map<type_index, vector<type_index>> m_manifest;
};

static EventManager eventManager;