#pragma once

class Vector2F
{
public:

    float x;
    float y;

    Vector2F(float, float);
    Vector2F(float[]);
    float length();
    void normalize();

    static float distance(const Vector2F &v1, const Vector2F &v2);
    static float dot(const Vector2F &v1,  const Vector2F &v2 );
    static Vector2F cross(const Vector2F &v1, const Vector2F &v2);

    Vector2F operator + (const Vector2F &other);
    Vector2F operator - (const Vector2F &other);
    Vector2F operator * (const Vector2F &other);
    Vector2F operator / (const Vector2F &other);

    Vector2F operator * (const float scalar);
    friend Vector2F operator * (const float scalar, const Vector2F &other);
    
    Vector2F& operator = (const Vector2F &other);
    Vector2F& operator += (const Vector2F &other);
    Vector2F& operator -= (const Vector2F &other);

    Vector2F operator + (void) const;
    Vector2F operator - (void) const;
};

