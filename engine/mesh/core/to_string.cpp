#include <engine/mesh/core.h>
#include "to_string.h"
using namespace std;

string std::to_string(glm::quat q)
{
	return string("(") 
	+ to_string(q.w) + "+"
	+ to_string(q.x) + "i+"
	+ to_string(q.y) + "j+"
	+ to_string(q.z) + "k)";
}

string std::to_string(glm::vec3 v)
{
	return string("[") 
	+ to_string(v.x) + ","
	+ to_string(v.y) + ","
	+ to_string(v.z) + "]";
}

string std::to_string(glm::vec4 v)
{
	return string("[") 
	+ to_string(v.x) + ","
	+ to_string(v.y) + ","
	+ to_string(v.y) + ","
	+ to_string(v.w) + "]";
}