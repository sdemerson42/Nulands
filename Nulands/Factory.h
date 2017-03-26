#pragma once

#include <vector>
#include <memory>
#include <tuple>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include "Events.h"

class Entity;
class IComponent;


using CMType = IComponent *(*)(Entity *);

class Factory
{
public:
	struct CompData
	{
		std::string type;
		std::vector<std::string> args;
		bool fromState;
		float x;
		float y;
	};
	using Blueprint = std::map<std::string, std::vector<CompData>>;
	void createBlueprints(const std::string &fName);
	void createEntity(std::vector<std::shared_ptr<Entity>> &v, const std::string &name, float x = 0, float y = 0, bool fromState = false);
	//void createEntity(std::vector<std::shared_ptr<Entity>> &v, std::stringstream &ss);
	//void createEntity(std::vector<std::shared_ptr<Entity>> &v, const Events::SpawnEvent &spawn);
	static std::map<std::string, CMType> *getMap()
	{
		if (m_makerMap == nullptr) m_makerMap = new std::map<std::string, CMType>;
		return m_makerMap;
	}
private:
	Blueprint m_blueprint;
	Blueprint m_stateBlueprint;
	bool stob(const std::string &s)
	{
		if (s == "true") return true;
		return false;
	}
	static std::map<std::string, CMType> *m_makerMap;
};

template<typename T>
class FactoryRegistry: public Factory
{
public:
	FactoryRegistry(const std::string &s)
	{
		getMap()->insert(std::make_pair(s, &makeComponent<T>));
	}
};


