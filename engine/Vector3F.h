#pragma once

class Vector3F
{
public:

    float x;
    float y;
    float z;

    Vector3F(float x_, float y_, float z_);
    void set(float x_, float y_, float z_);
    float length();
    void normalize();

    static float distance(const Vector3F &v1, const Vector3F &v2);
    static float dot(const Vector3F &v1,  const Vector3F &v2 );
    static Vector3F cross(const Vector3F &v1, const Vector3F &v2);

    Vector3F operator + (const Vector3F &other);
    Vector3F operator - (const Vector3F &other);
    Vector3F operator * (const Vector3F &other);
    Vector3F operator / (const Vector3F &other);

    Vector3F operator * (const float scalar);
    friend Vector3F operator * (const float scalar, const Vector3F &other);
    
    Vector3F& operator = (const Vector3F &other);
    Vector3F& operator += (const Vector3F &other);
    Vector3F& operator -= (const Vector3F &other);

    Vector3F operator + (void) const;
    Vector3F operator - (void) const;
};

