#pragma once

#include <vector>
#include <memory>
#include <tuple>
#include <string>
#include <map>
#include <fstream>

class Entity;

struct CompData
{
	std::string type;
	std::vector<std::string> args;
};

class Factory
{
public:
	using Blueprint = std::map<std::string, std::vector<CompData>>;
	void createBlueprints(const std::string &fName);
	void createEntity(std::vector<std::shared_ptr<Entity>> &v, const std::string &name);
private:
	Blueprint m_blueprint;
};


