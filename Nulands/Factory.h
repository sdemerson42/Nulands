#pragma once

#include <vector>
#include <memory>
#include <tuple>
#include <string>
#include <map>
#include <fstream>

class Entity;



class Factory
{
public:
	struct CompData
	{
		std::string type;
		std::vector<std::string> args;
	};
	using Blueprint = std::map<std::string, std::vector<CompData>>;
	void createBlueprints(const std::string &fName);
	void createEntity(std::vector<std::shared_ptr<Entity>> &v, const std::string &name, float x = 0, float y = 0);
private:
	Blueprint m_blueprint;
	bool stob(const std::string &s)
	{
		if (s == "true") return true;
		return false;
	}
	void addRenderC(Entity *e, const std::vector<std::string> &v);
	void addPhysicsC(Entity *e, const std::vector<std::string> &v);
	void addCameraC(Entity *e, const std::vector<std::string> &v);
	void addAnimatorC(Entity *e, const std::vector<std::string> &v);
	void addTilesC(Entity *e, const std::vector<std::string> &v);
	void addAnimation(Entity *e, const std::vector<std::string> &v);
};


