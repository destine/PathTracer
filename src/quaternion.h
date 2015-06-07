#ifndef __incl__quaternion
#define __incl__quaternion

#include "vector.h"

class Quaternion
{
    Vector3 m_vector;
    float m_scalar;

public:
    Quaternion(void)
    {
        m_scalar = 1;
    }

    Quaternion(const Vector3& vector, const float scalar = 0)
    {
        m_vector = vector;
        m_scalar = scalar;
    }

    Vector3 getVector(void) const
    {
        return m_vector;
    }

    float getScalar(void) const
    {
        return m_scalar;
    }

    Quaternion conjugate(void) const;

    Quaternion mul(const Quaternion& other) const;
};

#endif
