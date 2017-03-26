#include "Entity.h"
#include "IComponent.h"
#include "TilesComponent.h"

GTypes::EntityGuid Entity::m_guidCounter = 0;

void Entity::outState(std::ostream &ost)
{
	if (!m_persist) return;
	// Hacky interim solution
	bool hack = hasComponent<TilesComponent>();
	
	if (!hack)
		ost << "{ Entity" << m_guid << " ( " << m_position.x << " " << m_position.y << " )\n";
	for (auto &sp : m_component)
		ost << *sp.get();
	if (!hack)
		ost << "}\n";
}