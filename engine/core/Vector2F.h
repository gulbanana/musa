#pragma once
#include "Vector3F.h"

class Vector2F
{
public:

    float x;
    float y;

	//constructors
    Vector2F(float, float);
    Vector2F(float[]);
	Vector2F();

	//utility
    float length();
    void normalize();
    static float distance(const Vector2F &v1, const Vector2F &v2);
    static float dot(const Vector2F &v1,  const Vector2F &v2 );
    static Vector2F cross(const Vector2F &v1, const Vector2F &v2);

	//arithmetic
    Vector2F operator + (const Vector2F &other);
	Vector2F operator + () const;
    Vector2F operator - (const Vector2F &other);
    Vector2F operator - () const;
	Vector2F operator / (const Vector2F &other);
    Vector2F operator * (const Vector2F &other);
    Vector2F operator * (const float scalar);
    friend Vector2F operator * (const float scalar, const Vector2F &other);
    
	//combination
    Vector2F& operator = (const Vector2F &other);
    Vector2F& operator += (const Vector2F &other);
    Vector2F& operator -= (const Vector2F &other);

	//conversions
	operator Vector3F();
};

