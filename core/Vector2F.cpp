#include <cmath>
#include "Vector2F.h"

Vector2F::Vector2F(float x_, float y_)
{
    x = x_;
    y = y_;
}

float Vector2F::length()
{
    return (float)sqrt(x * x + y * y);
}

void Vector2F::normalize()
{
    float fLength = length();

    x = x / fLength;
    y = y / fLength;
}

#pragma region "Operators"
Vector2F Vector2F::operator + (const Vector2F &other)
{
    return Vector2F(x + other.x, y + other.y);
}

Vector2F Vector2F::operator + () const
{
    return *this;
}

Vector2F Vector2F::operator - (const Vector2F &other)
{
    return Vector2F(x - other.x, y - other.y);
}

Vector2F Vector2F::operator - () const
{
    return Vector2F(-x, -y);
}

Vector2F Vector2F::operator * (const Vector2F &other)
{
    return Vector2F(x * other.x, y * other.y);
}

Vector2F Vector2F::operator * (const float scalar)
{
    return Vector2F(x * scalar, y * scalar);
}

Vector2F operator * (const float scalar, const Vector2F &other)
{
    return Vector2F(other.x * scalar, other.y * scalar);
}

Vector2F Vector2F::operator / (const Vector2F &other)
{
    return Vector2F(x / other.x, y / other.y);
}

Vector2F& Vector2F::operator = (const Vector2F &other)
{
    x = other.x;
    y = other.y;

    return *this;
}

Vector2F& Vector2F::operator += (const Vector2F &other)
{
    x += other.x;
    y += other.y;

    return *this;
}

Vector2F& Vector2F::operator -= (const Vector2F &other)
{
    x -= other.x;
    y -= other.y;

    return *this;
}
#pragma endregion

#pragma region "Static"
static float distance(const Vector2F &v1,  const Vector2F &v2)
{
    float dx = v1.x - v2.x;
    float dy = v1.y - v2.y;

    return (float)sqrt(dx * dx + dy * dy);
}

static float dot(const Vector2F &v1,  const Vector2F &v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}
#pragma endregion

