#include "scene.h"

void NaiveScene::insertObject(Object* obj)
{
    m_objects.push_front(obj);
}

void NaiveScene::removeObject(Object* obj)
{
}

Color NaiveScene::computeBRDF(const Vector3& point, const Vector3& normal, const Ray& viewer, const Object* o) const
{
    Color reflected;

    Material m = o->getMaterial();
    LightListIter lIter;
    ObjectListIter oIter;

    bool blocked;

    Vector3 reflection;

    for (lIter = m_lights.begin(); lIter != m_lights.end(); ++lIter)
    {
        blocked = false;
        Ray toPoint = (*lIter)->getRayToPoint(point);

        for (oIter = m_objects.begin(); oIter != m_objects.end(); ++oIter)
        {
            if (*oIter != o && (*lIter)->isBlockedByObject(*oIter, toPoint))
            {
                blocked = true;
                break;
            }
        }

        if (!blocked)
        {
            reflected = reflected.add((*lIter)->colorObject(toPoint, normal, viewer, o));
        }
        else
        {
            reflected = reflected.add((*lIter)->getColor().mul(m.getAmbient()));
        }
    }

    return reflected;
}

Color NaiveScene::trace(const Ray& ray, int recursionDepth)
{
    if (recursionDepth < 0)
        return Color();

	//Iterate through objects and do ray-intersection tests
	bool intersects = false;
	
	float shortestT;
	ObjectListIter oIter;
	Primitive* primIntersects = NULL;
	Object* objIntersects = NULL;

    Ray rayObjectSpace;

    PrimitiveListIter pIter;
    float t;
    Vector3 shortestNormal;
    Vector3 normal;

	for (oIter = m_objects.begin(); oIter != m_objects.end(); ++oIter)
	{
        PrimitiveList p = (*oIter)->getPrimitives();
        rayObjectSpace = (*oIter)->getTransform().transformInverse(ray);

        for (pIter = p.begin(); pIter != p.end(); ++pIter)
        {
            if ((*pIter)->intersects(rayObjectSpace, t, normal))
            {
                if ((!intersects || t < shortestT) && t > 0)
                {
                    intersects = true;
                    shortestT = t;
                    primIntersects = *pIter;
                    objIntersects = *oIter;
                    shortestNormal = normal;
                }
            }
        }
	}

	//If no intersection, return blank Color
	if (!intersects)
	{
	    return Color(0, 0, 0);
	}

	//Have to put after intersects test since could be (0,0,0)
	shortestNormal = objIntersects->getTransform().transformNormal(shortestNormal);
	shortestNormal = shortestNormal.normalize();

    Vector3 incident = ray.getPoint(shortestT);
    Vector3 view = ray.getDirection().normalize().mul(-1);
    Vector3 reflect = shortestNormal.mul(2 * view.dot(shortestNormal)).sub(view);

    Vector3 push = reflect.mul(0.01);
    Ray reflection(incident.add(push), incident.add(reflect));

    Color seen = computeBRDF(incident, shortestNormal, ray, objIntersects);

    Material mat = objIntersects->getMaterial();
    Color reflective = mat.getReflective();

    seen = seen.add(trace(reflection, recursionDepth - 1).mul(reflective));

    return seen;
}

void AABBScene::insertObject(Object* obj)
{
    m_RootNode->insert(obj);
}

void AABBScene::removeObject(Object* obj)
{
    // heh its stuck
}

bool isLightBlocked(Light* source, const Vector3& point, AABBNode* tree)
{
    if (tree->getObject() == NULL)
    {
        return false;
    }

    Ray toPoint = source->getRayToPoint(point);

    if ((source)->isBlockedByObject(tree->getObject(), toPoint))
    {
        return true;
    }

    return isLightBlocked(source, point, tree->getLeft()) ||
           isLightBlocked(source, point, tree->getRight());
}

Color AABBScene::computeBRDF(const Vector3& point, const Vector3& normal, const Ray& viewer, const Object* o) const
{
    Color reflected;

    Material m = o->getMaterial();
    LightListIter lIter;

    Object* pCur = NULL;

    Vector3 reflection;

    for (lIter = m_lights.begin(); lIter != m_lights.end(); ++lIter)
    {
        if (!isLightBlocked(*lIter, point, m_RootNode))
        {
            Ray toPoint = (*lIter)->getRayToPoint(point);

            reflected = reflected.add((*lIter)->colorObject(toPoint, normal, viewer, o));
        }
        else
        {
            reflected = reflected.add((*lIter)->getColor().mul(m.getAmbient()));
        }
    }

    return reflected;
}

Color AABBScene::trace(const Ray& ray, int recursionDepth)
{
    if (recursionDepth < 0)
        return Color();

    Object* hitObject = NULL;
    Primitive* hitPrimitive = NULL;
    Vector3 hitPoint;
    Vector3 hitPointNormal;
    float hitTime = 0.0f;

    m_RootNode->queryObject(ray, hitObject, hitPrimitive, hitPoint,
	                    hitPointNormal, hitTime);

    if (hitObject == NULL)
        return Color(0, 0, 0);

    Vector3 view = ray.getDirection().normalize().mul(-1);
    Vector3 reflect = hitPointNormal.mul(2 * view.dot(hitPointNormal)).sub(view);

    Ray reflection(hitPoint, hitPoint.add(reflect));

    Color seen = computeBRDF(hitPoint, hitPointNormal, ray, hitObject);

    Material mat = hitObject->getMaterial();
    Color specular = mat.getSpecular();

    seen = seen.add(trace(reflection, recursionDepth - 1).mul(specular));

    return seen;
}
