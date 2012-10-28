#pragma once

//Time
typedef glm::highp_uint   microseconds;
typedef glm::mediump_uint milliseconds;
typedef glm::highp_float  seconds;

//Position
#if defined(GLM_PRECISION_HIGHP_FLOAT)
    typedef glm::highp_float coord;
	typedef glm::highp_vec3  point;
	typedef glm::highp_vec2  point2;
	typedef glm::highp_vec3  line;
#else
    typedef glm::mediump_float coord;
	typedef glm::mediump_vec3 point;
	typedef glm::mediump_vec2 point2;
	typedef glm::mediump_vec3 lnseg;
	typedef glm::mediump_quat rotation;
#endif

//raw orientation
typedef glm::mediump_float angle;
typedef glm::mediump_vec3 eulers;

//Material
typedef glm::lowp_vec4 colour;