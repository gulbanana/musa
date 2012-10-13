#pragma once
#include <cmath>
#include <array>
#include <cfloat>
#include <engine/platform.h>
template<typename T> class Vec2;

template <typename T>
struct Vec3
{
    T x, y, z;

#pragma region constructors
	Vec3(T x, T y, T z) : x(x), y(y), z(z) {}
	Vec3(std::array<T,3> xyz) : x(xyz[0]), y(xyz[1]), z(xyz[2]) {}
#pragma endregion

#pragma region utility
	static Vec3 origin()
	{
		return Vec3((T)0, (T)0, (T)0);
	}

	static Vec3 unit()
	{
		return Vec3((T)1, (T)1, (T)1);
	}

	T length() const 
	{ 
		auto result = sqrt(x * x + y * y + z * z);
        if (isnan(result)) return (T)0.0;
        
		else return (T)result;
	}

	void normalize()
	{
		T fLength = length(); 
		if (fLength == (T)0) return;
		x /= fLength; y /= fLength; z /= fLength;
	}

	void mod(T scalar)	{ x = fmod(x, scalar); y = fmod(y, scalar); z = fmod(z, scalar);}

    static T distance(Vec3 const& v1, Vec3 const& v2)
	{
		T dx = v1.x - v2.x;
		T dy = v1.y - v2.y;
		T dz = v1.z - v2.z;

		return (T)sqrt(dx * dx + dy * dy + dz * dz);
	}

    static T dot(Vec3 const& v1, Vec3 const& v2 )
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

    static Vec3 cross(Vec3 const& v1, Vec3 const& v2)
	{
		return Vec3(v1.y * v2.z - v1.z * v2.y,
				   -v1.x * v2.z + v1.z * v2.x,
					v1.x * v2.y - v1.y * v2.x);
	}

	static Vec3 midpoint(Vec3 const& v1, Vec3 const& v2)
	{
		return (v1 + v2) / (T)2.0;
	}
#pragma endregion

#pragma region operators
	Vec3 operator +(Vec3 const& other) const { return Vec3(x + other.x, y + other.y, z + other.z); }
	Vec3 operator -(Vec3 const& other) const { return Vec3(x - other.x, y - other.y, z - other.z); }
	Vec3 operator *(Vec3 const& other) const { return Vec3(x * other.x, y * other.y, z * other.z); }
	Vec3 operator /(Vec3 const& other) const { return Vec3(x / other.x, y / other.y, z / other.z); }

	Vec3 operator *(T scalar) const { return Vec3(x * scalar, y * scalar, z * scalar); }
	friend Vec3 operator *(T scalar, Vec3 const& other) { return Vec3(other.x * scalar, other.y * scalar, other.z * scalar); }
	Vec3 operator /(T scalar) const { return Vec3(x / scalar, y / scalar, z / scalar); }
    
    Vec3& operator =(Vec3 const& other) { x = other.x; y = other.y; z = other.z; return *this; }
    Vec3& operator +=(Vec3 const& other) { x += other.x; y += other.y; z += other.z; return *this; }
    Vec3& operator -=(Vec3 const& other) { x -= other.x; y -= other.y; z -= other.z; return *this; }
	Vec3& operator *=(T scalar) { x *= scalar; y *= scalar; z *= scalar; return *this; }

	Vec3 operator +() const { return *this; }
	Vec3 operator -() const { return Vec3(-x, -y, -z); }

	bool operator ==(Vec3 const& other) const { return x == other.x && y == other.y && z == other.z; }
	bool operator !=(Vec3 const& other) const { return x != other.x || y != other.y || z != other.z; }
#pragma endregion
};