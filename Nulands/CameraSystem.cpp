#include "CameraSystem.h"
#include "CameraComponent.h"
#include "Entity.h"

void CameraSystem::update()
{
	// NOTE: For now, camera movement depends on a single focus. Change this later.

	if (AutoList<CameraComponent>::size() == 0) return;
	auto c = AutoList<CameraComponent>::get(0);
	

}