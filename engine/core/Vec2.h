#pragma once
#include <array>
#include "Vec3.h"

template<typename T>
class Vec2
{
public:

    T x;
    T y;

#pragma region constructors
	Vec2(T x, T y) : x(x), y(y) {}
	Vec2(T xy[]) : x(xy[0]), y(xy[1]) {}
	explicit Vec2(Vec3<T> vec) : x(vec.x), y(vec.y) {}

#ifdef DOUBLE_PRECISION
	Vec2() : x(0.0), y(0.0) {}
#else
	Vec2() : x(0.f), y(0.f) {}
#endif
#pragma endregion

#pragma region utility
	T length() const { return (T)sqrt(x * x + y * y); } 
	void normalize() { T fLength = length(); x = x / fLength; y = y / fLength; }
	static T dot(Vec2 const& v1,  Vec2 const& v2 )	{ return v1.x * v2.x + v1.y * v2.y; }
	static T cross(Vec2 const& v1, Vec2 const& v2)	{ return v1.x * v2.y - v2.x * v1.y; }
	static T distance(Vec2 const& v1, Vec2 const& v2)
	{
		T dx = v1.x - v2.x;
		T dy = v1.y - v2.y;
		return sqrt(dx * dx + dy * dy);
	}
#pragma endregion

#pragma region arithmetic
	Vec2 operator +(Vec2 const& other)						{ return Vec2(x + other.x, y + other.y); }
	Vec2 operator +() const										{ return *this; }
	Vec2 operator -(Vec2 const& other)						{ return Vec2(x - other.x, y - other.y); }
	Vec2 operator -() const										{ return Vec2(-x, -y); }
	Vec2 operator /(Vec2 const& other)						{ return Vec2(x / other.x, y / other.y); }
	Vec2 operator *(Vec2 const& other)						{ return Vec2(x * other.x, y * other.y); }
	Vec2 operator *(T scalar)								{ return Vec2(x * scalar, y * scalar); }
	friend Vec2 operator *(T scalar, Vec2 const& other)	{ return Vec2(other.x * scalar, other.y * scalar); }
#pragma endregion
    
#pragma region assignment
	Vec2& operator =(Vec2 const& other)		{ x = other.x; y = other.y; return *this; }
	Vec2& operator +=(Vec2 const& other)	{ x += other.x; y += other.y; return *this; }
	Vec2& operator -=(Vec2 const& other)	{ x -= other.x; y -= other.y; return *this; }
#pragma endregion

#pragma region conversions
	operator Vec3<T>() { return Vec3<T>(x, y, (T)0.0); }
#pragma endregion
};