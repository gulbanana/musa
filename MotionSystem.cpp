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

void MotionSystem::frame()
{
	remove_if(begin(entities), end(entities), [](weak_ptr<IEntity> entity)
	{
		return entity.expired();
	});

	for_each(begin(entities), end(entities), [=](weak_ptr<IEntity> entity)
	{
		auto view = entity.lock();
		auto position = (Position2D*)view->get_component("Position2D").get();
		
		position->x += ((float)rand() / (float)RAND_MAX) - 0.5f;
		position->y += ((float)rand() / (float)RAND_MAX) - 0.5f;
	});
}