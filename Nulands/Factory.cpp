#include "Factory.h"
#include "Entity.h"
#include "RenderComponent.h"
#include "PhysicsComponent.h"
#include "AnimatorComponent.h"
#include "CameraComponent.h"
#include "TilesComponent.h"
#include "ParticleComponent.h"
#include "PlayerInputComponent.h"
#include "BehaviorComponent.h"

std::map<std::string, CMType> *Factory::m_makerMap;

std::istream &operator >> (std::istream &ist, Factory::CompData & cd)
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

	bool fromState = false;
	float sx = 0;
	float sy = 0;

	ist >> c;
	if (c != '(')
		ist.putback(c);
	else
	{
		fromState = true;
		ist >> sx >> sy >> c;
	}

	auto p = b.find(bName);
	if (p != b.end()) return ist;

	std::vector<Factory::CompData> v;

	while (true)
	{
		Factory::CompData cd;
		if (!(ist >> cd))
		{
			ist.clear();
			break;
		}
		cd.fromState = fromState;
		if (fromState)
		{
			cd.x = sx;
			cd.y = sy;
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

void Factory::createEntity(std::vector<std::shared_ptr<Entity>> &v, const std::string &name, float x, float y, bool fromState)
{

	Blueprint *b;

	if (fromState) b = &m_stateBlueprint;
	else b = &m_blueprint;

	auto p = b->find(name);
	if (p == b->end()) return;
	v.push_back(std::make_shared<Entity>());
	auto e = v[v.size() - 1].get();

	for (auto &c : p->second)
	{
		auto cm = m_makerMap->find(c.type);
		if (cm != m_makerMap->end())
		{
			e->m_component.push_back(shared_ptr<IComponent>(cm->second( e )));
			// Hack for Tilesets... Temporary
			auto t = e->getComponent<TilesComponent>();
			if (t != nullptr)
				t->m_vecRef = &v;
			e->m_component[e->m_component.size() - 1]->initialize(c.args);
			
			if (fromState)
			{
				x = c.x;
				y = c.y;
			}
		}
	}

	e->setPosition(x, y);
}

void Factory::createEntity(std::vector<std::shared_ptr<Entity>> &v, std::stringstream &ss)
{
	m_stateBlueprint.clear();
	ss.clear(ios_base::goodbit);
	while (ss)
		ss >> m_stateBlueprint;
	for (auto &p : m_stateBlueprint)
		createEntity(v, p.first, 0.0f, 0.0f, true);
}

void Factory::createEntity(std::vector<std::shared_ptr<Entity>> &v, const Events::SpawnEvent &spawn)
{
	v.push_back(std::make_shared<Entity>());
	auto e = v[v.size() - 1].get();
	auto p = m_blueprint.find(spawn.bName);
	for (auto &c : p->second)
	{
		auto cm = m_makerMap->find(c.type);
		if (cm != m_makerMap->end())
		{
			e->m_component.push_back(shared_ptr<IComponent>(cm->second(e)));
			// Hack for Tilesets... Temporary
			auto t = e->getComponent<TilesComponent>();
			if (t != nullptr)
				t->m_vecRef = &v;
			if (c.args.size() > 0 && c.args[0] == "*")
				e->m_component[e->m_component.size() - 1]->initialize(spawn.init);
			else
				e->m_component[e->m_component.size() - 1]->initialize(c.args);
		}
	}
	e->setPersist(spawn.persist);
	e->setPosition(spawn.x, spawn.y);
}

