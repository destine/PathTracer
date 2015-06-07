#ifndef __incl__view
#define __incl__view

#include "sampler.h"
#include "vector.h"

class View
{
    Vector3 m_ll_point;
    Vector3 m_basis_v1;
    Vector3 m_basis_v2;

public:
    View(void)
    {
        // empty view. :(
    }

    /* Constructs a new View object from the four corners of the
       projection plane represented as points in camera space. */
    View(Vector3 ll, Vector3 lr, Vector3 ul, Vector3 ur)
    {
        m_ll_point = ll;
        m_basis_v1 = lr.sub(ll);
        m_basis_v2 = ul.sub(ll);

        if (!ll.add(m_basis_v1.add(m_basis_v2)).equals(ur))
        {
            // error!
        }
    }
    
    virtual Vector3 getOrigin(void) {
        return m_ll_point;
    }
    
    virtual Vector3 getBasis1(void) {
        return m_basis_v1;
    }
    
    virtual Vector3 getBasis2(void) {
        return m_basis_v2;
    }

    Vector3 getPointFromSample(const Sample& sample) const
    {
        float weight1 = (sample.i + 0.5f) / (sample.source->getWidth());
        float weight2 = (sample.j + 0.5f) / (sample.source->getHeight());

        return m_ll_point.add(m_basis_v1.mul(weight1)).add(m_basis_v2.mul(weight2));
    }
};

#endif
