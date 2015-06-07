#ifndef __incl__camera
#define __incl__camera

#include "object.h"
#include "view.h"

class Camera : public Object
{
    Transform m_camToWorld;
    View m_view;

public:
    Camera(void)
    {
    }

    Camera(const Transform& camToWorld, const View& view)
    {
        m_camToWorld = camToWorld;
        m_view = view;
    }
  
    virtual Transform getTransform(void) const {
        return m_camToWorld;
    }
  
    virtual void setTransform(const Transform& t) {
        m_camToWorld = t;
    }
  
    virtual View getView(void) const {
        return m_view;
    }
  
    virtual void setView(const View& v) {
        m_view = v;
    }

    Ray generateRay(const Sample& sample) const;
};

#endif