#ifndef __incl__transform
#define __incl__transform

#include <cmath>
#include "matrix.h"
#include "ray.h"
#include "quaternion.h"
#include "vector.h"

class Transform
{
    Matrix4 m_transformTo;
    Matrix4 m_transformFrom;

public:
    Transform(void)
    {
        m_transformTo.set(0, 0, 1);
        m_transformTo.set(1, 1, 1);
        m_transformTo.set(2, 2, 1);
        m_transformTo.set(3, 3, 1);
        m_transformFrom = m_transformTo;
    }

    Transform concat(const Transform& other) const;

    Transform invert(void) const;

    /* Translate by <X, Y, Z>. */
    void translate(const float x, const float y, const float z);

    /* Rotate by DEGREE degrees about AXIS, counter-clockwise. */
    void rotate(const Vector3& axis, const float degree);

    /* Scale along three cartesian axis by X, Y, and Z. */
    void scale(const float x, const float y, const float z);

    void print(void) {
        printf("Transformation matrix:\n");
        Vector4 v0 = m_transformTo.getRow(0);
        Vector4 v1 = m_transformTo.getRow(1);
        Vector4 v2 = m_transformTo.getRow(2);
        Vector4 v3 = m_transformTo.getRow(3);

        printf("%f %f %f %f\n",v0.get(0),v0.get(1),v0.get(2),v0.get(3));
        printf("%f %f %f %f\n",v1.get(0),v1.get(1),v1.get(2),v1.get(3));
        printf("%f %f %f %f\n",v2.get(0),v2.get(1),v2.get(2),v2.get(3));
        printf("%f %f %f %f\n",v3.get(0),v3.get(1),v3.get(2),v3.get(3));
    }

    Ray transform(const Ray& ray) const;
    Vector3 transform(const Vector3& vector) const;

    Vector3 transformInverse(const Vector3& vector) const;
    Ray transformInverse(const Ray& ray) const;

    Vector3 transformNormal(const Vector3& vector) const;
};

#endif