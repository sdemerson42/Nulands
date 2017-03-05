#pragma once

#include <vector>
#include <memory>
#include <string>

#include "SFML\Graphics.hpp"

class Entity;
class ISystem;
class Factory;

class NuScene
{
public:
	NuScene(const std::string &fName);
	void initialize();
	void close();
private:
	std::vector<std::shared_ptr<Entity>> m_entityVec;
	std::shared_ptr<Factory> m_factory;
	sf::RenderWindow *m_window;
	std::string m_dataFName;
};