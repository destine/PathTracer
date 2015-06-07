#include <iostream>
#include "light.h"
#include "vector.h"

using namespace std;

#define EPSILON 0.01

Ray PointLight::getRayToPoint(const Vector3& point) const
{
    return Ray(m_position, point);
}

bool PointLight::isBlockedByObject(const Object* o, const Ray& r) const {
    PrimitiveList pList = o->getPrimitives();
    PrimitiveListIter pIter;

    bool blocked = false;
    float t;
    Vector3 normal;

    Ray rayObjectSpace = o->getTransform().transformInverse(r);

    for (pIter = pList.begin(); pIter != pList.end(); ++pIter)
    {
        if ((*pIter)->intersects(rayObjectSpace, t, normal))
        {
            if (t > EPSILON && t < 1 - EPSILON)
            {
                blocked = true;
                break;
            }
        }
    }
    
    return blocked;
}

Color PointLight::colorObject(const Ray& incident, const Vector3& normal, const Ray& viewer, const Object* o) const {
    //TODO: implement falloff
    Vector3 light = incident.getDirection().normalize().mul(-1);

    Material m = o->getMaterial();

    // compute ambient component
    Color ambient = m.getAmbient().mul(getColor());

    // compute lambertian component
    float lnDot = std::max(0.0f, light.dot(normal));
    Color diffuse = m.getDiffuse().mul(getColor()).mul(lnDot);

    // compute specular component
    Vector3 reflect = normal.mul(2 * light.dot(normal)).sub(light);
    reflect = reflect.normalize();

    Vector3 view = viewer.getDirection().normalize().mul(-1);

    float rvDot = std::pow(std::max(0.0f, reflect.dot(view)), m.getPower());

    Color specular = m.getSpecular().mul(getColor()).mul(rvDot);

    return ambient.add(diffuse).add(specular);
}

Ray DirectionalLight::getRayToPoint(const Vector3& point) const {
    Ray r(point.sub(m_position), point);
    return r;
}

bool DirectionalLight::isBlockedByObject(const Object* o, const Ray& r) const
{
    PrimitiveList pList = o->getPrimitives();
    PrimitiveListIter pIter;
    float t;
    Vector3 normal;
    Ray rayObjectSpace = o->getTransform().transformInverse(r);

    for (pIter = pList.begin(); pIter != pList.end(); ++pIter)
    {
        if ((*pIter)->intersects(rayObjectSpace, t, normal))
    {
        if (t < 1 - EPSILON)
        {
            return true;
            }
        }
    }

    return false;    
}

Color DirectionalLight::colorObject(const Ray& incident, const Vector3& normal, const Ray& viewer, const Object* o) const
{
    //TODO: implement falloff
    Vector3 light = incident.getDirection().normalize().mul(-1);

    Material m = o->getMaterial();

    // compute ambient component
    Color ambient = m.getAmbient().mul(getColor());

    // compute lambertian component
    float lnDot = std::max(0.0f, light.dot(normal));
    Color diffuse = m.getDiffuse().mul(getColor()).mul(lnDot);

    // compute specular component
    Vector3 reflect = normal.mul(2 * light.dot(normal)).sub(light);
    reflect = reflect.normalize();

    Vector3 view = viewer.getDirection().normalize().mul(-1);

    float rvDot = std::pow(std::max(0.0f, reflect.dot(view)), m.getPower());

    Color specular = m.getSpecular().mul(getColor()).mul(rvDot);

    return ambient.add(diffuse).add(specular);
}

Ray AmbientLight::getRayToPoint(const Vector3& point) const
{
    return Ray();
}

bool AmbientLight::isBlockedByObject(const Object* o, const Ray& r) const
{
    return false;
}

Color AmbientLight::colorObject(const Ray& pointToLight, const Vector3& normal, const Ray& viewer, const Object* o) const {
    Material m = o->getMaterial();
    return m.getAmbient().mul(getColor());
}
