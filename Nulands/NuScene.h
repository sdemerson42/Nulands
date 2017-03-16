#pragma once

#include <vector>
#include <memory>
#include <string>
#include <sstream>
#include "Events.h"

#include "SFML\Graphics.hpp"
#include "EventManager.h"

class Entity;
class ISystem;
class Factory;

class NuScene : public EventHandler
{
public:
	NuScene(const std::string &fName);
	virtual ~NuScene()
	{
		eventManager.unregisterListener(this);
	}
	void initialize(std::vector<std::shared_ptr<Entity>> &persistentVec);
	void close();
private:
	void initFromFile(std::vector<std::shared_ptr<Entity>> &persistentVec);
	void initFromState();
	std::vector<std::shared_ptr<Entity>> m_entityVec;
	std::shared_ptr<Factory> m_factory;
	sf::RenderWindow *m_window;
	std::string m_dataFName;
	std::stringstream m_stateImage;
	bool m_activeScene;
	void onInstantiate(const Events::Instantiate *evnt);
};