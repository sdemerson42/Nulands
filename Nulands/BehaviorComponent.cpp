#include "BehaviorComponent.h"
#include "IBehavior.h"
#include <algorithm>

void BehaviorComponent::update()
{
	for (auto &sp : m_behavior)
		sp->update();
}

void BehaviorComponent::outState(std::ostream &ost) const
{
	ost << "{ Behavior " << m_behavior.size() << " ";
	for (auto &sp : m_behavior)
		ost << sp->getTag() << " ";
	ost << "}\n";
}

void BehaviorComponent::addBehaviorByTag(const std::string &tag, IComponent *parent)
{
	/*
	if (tag == "test")
		addBehavior<TestBehavior>(this);
		*/
}

void BehaviorComponent::removeBehaviorByTag(const std::string &tag)
{
	auto p = std::find_if(m_behavior.begin(), m_behavior.end(), [tag](std::shared_ptr<IBehavior> &sp)
	{
		return sp->getTag() == tag;
	});
	if (p != m_behavior.end())
		m_behavior.erase(p);
}