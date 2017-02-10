#pragma once

#include <vector>
#include <memory>
#include <algorithm>

#include "EventHandler.h"
#include "IComponent.h"
#include "GTypes.h"

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
	GTypes::EntityGuid guid() const
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
	template<typename Comp>
	bool hasComponent()
	{
		auto it = std::find_if(m_component.begin(), m_component.end(), [](std::shared_ptr<IComponent>& sp) { return typeid(*sp.get()) == typeid(Comp); });
		if (it == m_component.end()) return false;
		return true;
	}
	void update()
	{
		for (auto& p : m_component)
			p->update();
	}
private:
	std::vector<std::shared_ptr<IComponent>> m_component;
	GTypes::EntityGuid m_guid;
	static GTypes::EntityGuid m_guidCounter;
};

GTypes::EntityGuid Entity::m_guidCounter = 0;
