#include "MotionSystem.h"
#include "CPosition2D.h"
#include "CVelocity2D.h"
#include "CCollision.h"
#include <array>
#include <iterator>
#include <typeinfo>
#include <iostream>
using namespace std;

vector<string> MotionSystem::required_components()
{
	array<string,2> compTypes = {"Position2D", "Velocity2D"};
	return vector<string>(compTypes.begin(), compTypes.end());
}

void MotionSystem::on_entity(shared_ptr<IEntity> entity)
{
	auto position = static_cast<CPosition2D*>(entity->get_component("Position2D"));
	auto velocity = static_cast<CVelocity2D*>(entity->get_component("Velocity2D"));
		
	if (entity->has_component("Collision"))
	{
		auto collision = static_cast<CCollision*>(entity->get_component("Collision"));
		
		if (collision->collidedX) velocity->x *= -1.f;
		if (collision->collidedY) velocity->y *= -1.f;
	}

	position->prevX = position->x;
	position->x += velocity->x;

	position->prevY = position->y;
	position->y += velocity->y;
}