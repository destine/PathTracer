#include <iostream>
#include "camera.h"

Ray Camera::generateRay(const Sample& sample) const
{
    Vector3 start = m_camToWorld.transform(Vector3());
    Vector3 end = m_view.getPointFromSample(sample);
    return Ray(start, end);
}
