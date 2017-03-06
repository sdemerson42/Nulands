#pragma once

#include <vector>
#include <memory>
#include <string>
#include <sstream>

#include "SFML\Graphics.hpp"

class Entity;
class ISystem;
class Factory;

class NuScene
{
public:
	NuScene(const std::string &fName);
	void initialize(std::vector<std::shared_ptr<Entity>> &persistentVec, bool fromState = false);
	void close();
private:
	void initFromFile(std::vector<std::shared_ptr<Entity>> &persistentVec);
	void initFromState();
	std::vector<std::shared_ptr<Entity>> m_entityVec;
	std::shared_ptr<Factory> m_factory;
	sf::RenderWindow *m_window;
	std::string m_dataFName;
	std::stringstream m_stateImage;
};