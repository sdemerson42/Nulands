#include "QuadTree.h"
#include "Entity.h"
#include "PhysicsComponent.h"

void QuadTree::initialize(float x, float y, float w, float h, int layer)
{
	m_bound.x = x;
	m_bound.y = y;
	m_bound.w = w;
	m_bound.h = h;
	m_curLayer = layer;
}

int QuadTree::getIndex(PhysicsComponent *pc, bool insert)
{
	float midX = m_bound.x + m_bound.w / 2.0f;
	float midY = m_bound.y + m_bound.h / 2.0f;
	float x = pc->getParent()->position().x;
	if (insert)
		x += pc->momentum().x;
	float y = pc->getParent()->position().y;
	if (insert)
		y += pc->momentum().y;
	float l = x + pc->collisionBox().x;
	float t = y + pc->collisionBox().y;
	float r = l + pc->collisionBox().w - 1;
	float b = t + pc->collisionBox().h - 1;

	if (r < midX && b < midY) return 0;
	if (l >= midX && b < midY) return 1;
	if (r < midX && t >= midY) return 2;
	if (l >= midX && t >= midY) return 3;

	return -1;
}

void QuadTree::quadSect()
{
	float w = m_bound.w / 2.0f;
	float h = m_bound.h / 2.0f;
	float midX = m_bound.x + w;
	float midY = m_bound.y + h;
	m_node.push_back(QuadTree{});
	m_node[m_node.size() - 1].initialize(m_bound.x, m_bound.y, w, h, m_curLayer + 1);
	m_node.push_back(QuadTree{});
	m_node[m_node.size() - 1].initialize(midX, m_bound.y, w, h, m_curLayer + 1);
	m_node.push_back(QuadTree{});
	m_node[m_node.size() - 1].initialize(midX, midY, w, h, m_curLayer + 1);
	m_node.push_back(QuadTree{});
	m_node[m_node.size() - 1].initialize(m_bound.x, midY, w, h, m_curLayer + 1);
}

void QuadTree::insert(PhysicsComponent *pc)
{
	if (m_node.size() > 0)
	{
		int index = getIndex(pc);
		if (index != -1)
		{
			m_node[index].insert(pc);
			return;
		}
	}
	
	m_pc.push_back(pc);

	if (m_curLayer < m_maxLayer && m_pc.size() > m_maxPc)
	{
		if (m_node.size() == 0)
			quadSect();
		for (int i = 0; i < m_pc.size(); ++i)
		{
			int index = getIndex(m_pc[i]);
			if (index != -1)
			{
				m_node[index].insert(m_pc[i]);
				m_pc.erase(m_pc.begin() + i);
				--i;
			}
		}
	}
}

void QuadTree::retrieve(std::vector<PhysicsComponent *> &vec, PhysicsComponent *pc)
{
	if (m_node.size() > 0)
	{
		int index = getIndex(pc);
		if (index != -1)
			m_node[index].retrieve(vec, pc);
		else
		{
			for (auto &n : m_node)
				n.retrieve(vec, pc);
		}
	}
	for (auto p : m_pc)
		if (p != pc)
			vec.push_back(p);
}

void QuadTree::clear()
{
	for (auto &q : m_node)
	{
		q.clear();
	}
	m_node.clear();
	m_pc.clear();

}