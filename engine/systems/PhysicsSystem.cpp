#include <array>
#include "../components.h"
#include "PhysicsSystem.h"
using namespace std;

vector<CMP> PhysicsSystem::required_components() const 
{
	array<CMP,1> compTypes = {CMP::Physics};
	return vector<CMP>(compTypes.begin(), compTypes.end());
}

void PhysicsSystem::on_entity(shared_ptr<IEntity> entity)
{
	//auto physics = entity->get_component<CPhysics>();
}