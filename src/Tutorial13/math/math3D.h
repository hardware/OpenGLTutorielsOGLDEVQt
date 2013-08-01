#ifndef MATH3D_H
#define MATH3D_H

#define _USE_MATH_DEFINES
#include <cmath>

#define ToRadian(x) (float)(((x) * 3.14159265359 / 180.0f))
#define ToDegree(x) (float)(((x) * 180.0f / 3.14159265359))

struct Vector3f
{
    float x;
    float y;
    float z;

    Vector3f()
    {
    }

    Vector3f(float _x, float _y, float _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }

    Vector3f Cross(const Vector3f& v) const;
    Vector3f& Normalize();
};

#endif // MATH3D_H
