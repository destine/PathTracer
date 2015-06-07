#include "ray.h"

Vector3 Ray::getStart(void) const
{
    return m_start;
}

Vector3 Ray::getEnd(void) const
{
    return m_end;
}

Vector3 Ray::getDirection(void) const
{
    return m_end.sub(m_start);
}

Vector3 Ray::getPoint(float t) const
{
    return m_start.add(getDirection().mul(t));
}
