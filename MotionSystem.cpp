#include "MotionSystem.h"
#include "Position2D.h"
#include <array>
#include <iterator>
#include <typeinfo>
#include <random>
using namespace std;

vector<string> MotionSystem::required_components()
{
	array<string,1> compTypes = {"Position2D"};
	return vector<string>(compTypes.begin(), compTypes.end());
}

void MotionSystem::on_entity(shared_ptr<IEntity> entity)
{
	auto position = static_cast<Position2D*>(entity->get_component("Position2D"));
		
	position->x += ((float)rand() / (float)RAND_MAX) - 0.5f;
	position->y += ((float)rand() / (float)RAND_MAX) - 0.5f;
}