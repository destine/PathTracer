#include "quaternion.h"

Quaternion Quaternion::conjugate(void) const
{
    Quaternion result;

    result.m_vector = m_vector.mul(-1);
    result.m_scalar = m_scalar;

    return result;
}

Quaternion Quaternion::mul(const Quaternion& other) const
{
    Quaternion result;

    result.m_vector = m_vector.mul(other.m_scalar);
    result.m_vector = result.m_vector.add(other.m_vector.mul(m_scalar));
    result.m_vector = result.m_vector.add(other.m_vector.cross(m_vector));

    result.m_scalar = m_scalar * other.m_scalar -
                      m_vector.dot(other.m_vector);

    return result;
}
