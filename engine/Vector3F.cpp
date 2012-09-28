#include <cmath>
#include "Vector3F.h"

Vector3F::Vector3F(float x_, float y_, float z_)
{
    x = x_;
    y = y_;
    z = z_;
}

float Vector3F::length()
{
    return (float)sqrt(x * x + y * y + z * z);
}

void Vector3F::normalize()
{
    float fLength = length();

    x /= fLength;
    y /= fLength;
    z /= fLength;
}

#pragma region "Operators"
Vector3F Vector3F::operator + (const Vector3F &other)
{
    return Vector3F(x + other.x, y + other.y, z + other.z);
}

Vector3F Vector3F::operator + () const
{
    return *this;
}

Vector3F Vector3F::operator - (const Vector3F &other)
{
    return Vector3F(x - other.x, y - other.y, z - other.z);
}

Vector3F Vector3F::operator - () const
{
    return Vector3F(-x, -y, -z);
}

Vector3F Vector3F::operator * (const Vector3F &other)
{
    return Vector3F(x * other.x, y * other.y, z * other.z);

}

Vector3F Vector3F::operator * (const float scalar)
{
    return Vector3F(x * scalar, y * scalar, z * scalar);
}

Vector3F operator * (const float scalar, const Vector3F &other)
{
	return Vector3F(other.x * scalar, other.y * scalar, other.z * scalar);
}

Vector3F Vector3F::operator / (const Vector3F &other)
{
    return Vector3F(x * other.x, y * other.y, z * other.z);
}

Vector3F& Vector3F::operator = (const Vector3F &other)
{
    x = other.x;
    y = other.y;
    z = other.z;

    return *this;
}

Vector3F& Vector3F::operator += (const Vector3F &other)
{
    x += other.x;
    y += other.y;
    z += other.z;

    return *this;
}

Vector3F& Vector3F::operator -= (const Vector3F &other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;

    return *this;
}
#pragma endregion

#pragma region Static
static float distance(const Vector3F &v1,  const Vector3F &v2)
{
    float dx = v1.x - v2.x;
    float dy = v1.y - v2.y;
    float dz = v1.z - v2.z;

    return (float)sqrt(dx * dx + dy * dy + dz * dz);
}

static float dot(const Vector3F &v1,  const Vector3F &v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

static Vector3F cross(const Vector3F &v1,  const Vector3F &v2)
{
    return Vector3F(v1.y * v2.z - v1.z * v2.y,
				   -v1.x * v2.z + v1.z * v2.x,
					v1.x * v2.y - v1.y * v2.x);
}
#pragma endregion

