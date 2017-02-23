#pragma once

#include <vector>
#include "GTypes.h"

class PhysicsComponent;

class QuadTree
{
public:
	QuadTree(float x, float y, float w, float h, int layer = 0) :
		m_curLayer{ layer }, m_bound{ x, y, w, h }
	{}
	void insert(PhysicsComponent *pc);
	void retrieve(std::vector<PhysicsComponent *> &vec, PhysicsComponent *pc);
private:
	int m_maxLayer = 5;
	int m_maxPc = 10;
	int m_curLayer;
	GTypes::Rect m_bound;
	std::vector<QuadTree> m_node;
	std::vector<PhysicsComponent *> m_pc;
	int getIndex(PhysicsComponent *pc);
	void quadSect();
};