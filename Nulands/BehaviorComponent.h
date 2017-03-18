#pragma once

#include "IComponent.h"
#include "AutoList.h"
#include <vector>
#include <memory>
#include <typeindex>
#include <algorithm>
#include <string>

class IBehavior;

class BehaviorComponent : public IComponent, public AutoList<BehaviorComponent>
{
public:
	BehaviorComponent(Entity *parent) :
		IComponent{ parent }
	{}
	void update() override;
	void outState(std::ostream &ost) const override;
	template<typename B, typename ...Args>
	void addBehavior(Args ...args)
	{
		m_behavior.push_back(std::make_shared<B>(args...));
	}
	void addBehaviorByTag(const std::string &tag, IComponent *parent);
	template<typename B>
	void removeBehavior()
	{
		std::type_index match{ std::type_index{typeid(B)} };
		auto p = find_if(m_behavior.begin(), m_behavior.end(), [match](std::shared_ptr<IBehavior> &sp)
		{
			return match == type_index{ typeid(*sp.get()) };
		});
		if (p != m_behavior.end())
			m_behavior.erase(p);
	}
	void removeBehaviorByTag(const std::string &tag);
private:
	std::vector<std::shared_ptr<IBehavior>> m_behavior;
};
