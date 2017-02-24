#pragma once

#include <vector>
#include <memory>

class Entity;

class Factory
{
public:
	// TEMPORARY - Will be replaced with data-driven constrruction.
	enum class EType { TestBox, TestWall };
	void construct(std::vector<std::shared_ptr<Entity>> &v, EType e, float x, float y);
};