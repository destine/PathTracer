#include "object.h"

Transform Object::getTransform(void) const
{
    return m_transform;
}

Material Object::getMaterial(void) const
{
    return m_material;
}

void Object::setTransform(const Transform& transform)
{
    m_transform = transform;
}

void Object::setMaterial(const Material& material) {
	m_material = material;
}

void Object::appendPrimitive(Primitive* primitive)
{
    m_primitiveList.push_front(primitive);
}
