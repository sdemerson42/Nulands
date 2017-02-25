#include "Factory.h"
#include "Entity.h"
#include "RenderComponent.h"
#include "PhysicsComponent.h"

#define addC(T, ...) addComponent<##T>(__VA_ARGS__)

std::istream &operator >> (std::istream &ist, CompData & cd)
{
	char c;
	if (!(ist >> c) || c != '{')
	{
		ist.putback(c);
		ist.clear(std::ios_base::failbit);
		return ist;
	}
	
	std::string cdType;
	ist >> cdType;
	cd.type = cdType;

	while (true)
	{
		std::string token;
		ist >> token;
		if (token == "}")
		{
			break;
		}
		cd.args.push_back(token);
	}
	
	
	return ist;
}

std::istream &operator >> (std::istream &ist, Factory::Blueprint &b)
{
	char c;
	if (!(ist >> c) || c != '{')
	{
		ist.clear(std::ios_base::failbit);
		return ist;
	}

	std::string bName;
	ist >> bName;
	auto p = b.find(bName);
	if (p != b.end()) return ist;

	std::vector<CompData> v;

	while (true)
	{
		CompData cd;
		if (!(ist >> cd))
		{
			ist.clear();
			break;
		}
		v.push_back(cd);
	}

	ist >> c;
	b[bName] = v;
	return ist;
}



void Factory::createBlueprints(const std::string &fName)
{
	std::ifstream f{ "Data\\" + fName };
	while (f)
		f >> m_blueprint;
}

void Factory::createEntity(std::vector<std::shared_ptr<Entity>> &v, const std::string &name)
{
	auto p = m_blueprint.find(name);
}