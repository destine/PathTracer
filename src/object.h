#ifndef __incl__object
#define __incl__object

#include "primitive.h"
#include "transform.h"
#include "material.h"

#include <forward_list>

class Object
{
    std::forward_list<Primitive*> m_primitiveList;
    Transform m_transform;
    Material m_material;

    public:
        Object(void)
        {
        }

        Transform getTransform(void) const;
        Material getMaterial(void) const;

        void setTransform(const Transform& transform);
        void setMaterial(const Material& material);

        void appendPrimitive(Primitive* primitive);
        
        std::forward_list<Primitive*> getPrimitives(void) const {
            return m_primitiveList;
        }
};

#endif
