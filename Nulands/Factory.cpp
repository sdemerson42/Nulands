#include "Factory.h"
#include "Entity.h"
#include "RenderComponent.h"
#include "PhysicsComponent.h"
#include "AnimatorComponent.h"
#include "CameraComponent.h"
#include "TilesComponent.h"
#include "ParticleComponent.h"
#include "PlayerInputComponent.h"

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
		if (c.type == "Render") addRenderC(e, c.args);
		if (c.type == "Physics") addPhysicsC(e, c.args);
		if (c.type == "Animator") addAnimatorC(e, c.args);
		if (c.type == "Animation") addAnimation(e, c.args);
		if (c.type == "Tiles") addTilesC(e, c.args);
		if (c.type == "Camera") addCameraC(e, c.args);
		if (c.type == "Particle") addParticle(e, c.args);
		if (c.type == "PlayerInput") addPlayerInput(e, c.args);
	}

	e->setPosition(x, y);
}

void Factory::createEntity(std::vector<std::shared_ptr<Entity>> &v, std::stringstream &ss)
{
	m_stateBlueprint.clear();
	while (ss)
		ss >> m_stateBlueprint;
	for (auto &p : m_stateBlueprint)
		for (auto &c : p.second)
			createEntity(v, p.first, c.x, c.y, true);
}




void Factory::addRenderC(Entity *e, const std::vector<std::string> &v)
{
	e->addComponent<RenderComponent>(e, v[0], stof(v[1]), stof(v[2]), stof(v[3]), stof(v[4]));
}

void Factory::addPhysicsC(Entity *e, const std::vector<std::string> &v)
{
	e->addComponent<PhysicsComponent>(e, stof(v[0]), stof(v[1]), stof(v[2]), stof(v[3]), stob(v[4]), stob(v[5]), stob(v[6]));
}

void Factory::addCameraC(Entity *e, const std::vector<std::string> &v)
{
	e->addComponent<CameraComponent>(e, stof(v[0]), stof(v[1]), stof(v[2]), stof(v[3]), stof(v[4]), stof(v[5]), stof(v[6]), stof(v[7]), stof(v[8]), stof(v[9]), stof(v[10]));
}
void Factory::addAnimatorC(Entity *e, const std::vector<std::string> &v)
{
	e->addComponent<AnimatorComponent>(e);
}

void Factory::addParticle(Entity *e, const std::vector<std::string> &v)
{
	e->addComponent<ParticleComponent>(e, stof(v[0]), stof(v[1]), stof(v[2]), stof(v[3]), ParticleComponent::EmitPattern::Directional,
		stoi(v[4]), stof(v[5]), stof(v[6]), stof(v[7]), stof(v[8]), v[9], stof(v[10]), stof(v[11]), stof(v[12]), stof(v[13]), stof(v[14]), stof(v[15]));
}

void Factory::addAnimation(Entity *e, const std::vector<std::string> &v)
{
	auto a = e->getComponent<AnimatorComponent>();
	if (a == nullptr) return;
	std::string name = v[0];
	int fCount = stoi(v[1]);
	vector<float> av;
	int i = 2;
	while (i < fCount * 4 + 2)
	{
		av.push_back(stof(v[i]));
		++i;
	}
	int speed = stoi(v[i]);
	bool loop = stob(v[i + 1]);
	a->addAnimation(AnimatorComponent::Animation{ name, av, speed, loop });
}

void Factory::addTilesC(Entity *e, const std::vector<std::string> &v)
{
	e->addComponent<TilesComponent>(e, v[0]);
}

void Factory::addPlayerInput(Entity *e, const std::vector<std::string> &v)
{
	e->addComponent<PlayerInputComponent>(e);
}