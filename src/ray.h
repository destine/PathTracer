#ifndef __incl__ray
#define __incl__ray

#include "vector.h"

class Ray
{
    Vector3 m_start;
    Vector3 m_end;

public:
    Ray(void)
    {
    }

    Ray(const Vector3& start, const Vector3& end)
    {
        m_start = start;
        m_end = end;
    }

    Vector3 getStart(void) const;
    Vector3 getEnd(void) const;

    Vector3 getDirection(void) const;

    Vector3 getPoint(float t) const;
};

#endif
