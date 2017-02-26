#pragma once

#include <vector>
#include <memory>
#include <algorithm>

#include "EventManager.h"
#include "IComponent.h"
#include "GTypes.h"
#include "SFML\Graphics.hpp"

class Entity: public EventHandler, public AutoList<Entity>
{
public:
	Entity()
	{
		m_guid = m_guidCounter;
		++m_guidCounter;
	}
	Entity(float x, float y) :
		Entity{}
	{
		m_position.x = x;
		m_position.y = y;
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
	Comp* getComponent()
	{
		auto it = std::find_if(m_component.begin(), m_component.end(), [](std::shared_ptr<IComponent>& sp) { return typeid(*sp.get()) == typeid(Comp); });
		if (it == m_component.end()) return nullptr;
		return static_cast<Comp *>(it->get());
	}
	template<typename Comp>
	bool hasComponent()
	{
		auto it = std::find_if(m_component.begin(), m_component.end(), [](std::shared_ptr<IComponent>& sp) { return typeid(*sp.get()) == typeid(Comp); });
		if (it == m_component.end()) return false;
		return true;
	}
	const sf::Vector2f &position() const
	{
		return m_position;
	}
	void setPosition(const sf::Vector2f &pos)
	{
		m_position.x = pos.x;
		m_position.y = pos.y;
	}
	void setPosition(float x, float y)
	{
		m_position.x = x;
		m_position.y = y;
	}
	void addPosition(float x, float y)
	{
		m_position.x += x;
		m_position.y += y;
	}
	void update()
	{
		for (auto& p : m_component)
			p->update();
	}
	void setActive(bool b)
	{
		m_active = b;
		for (auto sp : m_component)
			sp->setActive(b);
	}
	bool active() const
	{
		return m_active;
	}
private:
	std::vector<std::shared_ptr<IComponent>> m_component;
	GTypes::EntityGuid m_guid;
	sf::Vector2f m_position;
	bool m_active{ true };
	static GTypes::EntityGuid m_guidCounter;
};

