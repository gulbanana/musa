#include "MotionSystem.h"
#include "Position2D.h"
#include <array>
#include <iterator>
#include <typeinfo>
using namespace std;

vector<string> MotionSystem::required_components()
{
	array<string,1> compTypes = {typeid(Position2D).raw_name()};
	return vector<string>(compTypes.begin(), compTypes.end());
}

void MotionSystem::frame()
{
}