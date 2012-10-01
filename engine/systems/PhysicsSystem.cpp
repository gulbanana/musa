#include <array>
#include "../components.h"
#include "PhysicsSystem.h"
using namespace std;

vector<CID> PhysicsSystem::required_components()
{
	array<CID,1> compTypes = {CID::Physics};
	return vector<CID>(compTypes.begin(), compTypes.end());
}

void PhysicsSystem::on_entity(shared_ptr<IEntity> entity)
{
	//auto physics = entity->get_component<CPhysics>();
}