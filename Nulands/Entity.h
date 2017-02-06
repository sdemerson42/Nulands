#pragma once

#include <vector>
#include <memory>
#include <algorithm>

#include "EventHandler.h"
#include "IComponent.h"

class Entity: public EventHandler, public AutoList<Entity>
{
public:
	Entity()
	{
		m_guid = m_guidCounter;
		++m_guidCounter;
	}
	virtual ~Entity()
	{}
	unsigned long long guid() const
	{
		return m_guid;
	}
	template<typename Comp, typename ...Args>
	void addComponent(Args ...args)
	{
		m_component.push_back(std::make_shared<Comp>(args...));
	}
	template<typename Comp>
	IComponent* getComponent()
	{
		auto it = std::find_if(m_component.begin(), m_component.end(), [](std::shared_ptr<IComponent>& sp) { return typeid(*sp.get()) == typeid(Comp); });
		if (it == m_component.end()) return nullptr;
		return it->get();
	}
	void update()
	{
		for (auto& p : m_component)
			p->update();
	}
private:
	std::vector<std::shared_ptr<IComponent>> m_component;
	unsigned long long m_guid;
	static unsigned long long m_guidCounter;
};

unsigned long long Entity::m_guidCounter = 0;