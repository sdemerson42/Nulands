#pragma once

#include <vector>
#include "GTypes.h"

class PhysicsComponent;

class QuadTree
{
public:
	void initialize(float x, float y, float w, float h, int layer = 0);
	void insert(PhysicsComponent *pc);
	void retrieve(std::vector<PhysicsComponent *> &vec, PhysicsComponent *pc);
	void clear();
private:
	int m_maxLayer = 4;
	int m_maxPc = 20;
	int m_curLayer;
	GTypes::Rect m_bound;
	std::vector<QuadTree> m_node;
	std::vector<PhysicsComponent *> m_pc;
	int getIndex(PhysicsComponent *pc, bool insert = false);
	void quadSect();
};