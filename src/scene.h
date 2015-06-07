#ifndef __incl__scene
#define __incl__scene

#include <forward_list>

#include "camera.h"
#include "film.h"
#include "object.h"
#include "ray.h"
#include "sampler.h"
#include "light.h"

class Scene
{
    Camera m_camera;

public:
    Scene(void)
    {
    }

    virtual ~Scene(void)
    {
    }

    virtual void setCamera(const Camera& camera)
    {
        m_camera = camera;
    }

    virtual const Camera& getCamera(void) const
    {
        return m_camera;
    }

    virtual void insertLightSource(Light* l) = 0;
    virtual void insertObject(Object* obj) = 0;
    virtual void removeObject(Object* obj) = 0;

    virtual Color trace(const Ray& ray, int recursionDepth) = 0;
    virtual Color computeBRDF(const Vector3& point,
                              const Vector3& normal,
                              const Ray& viewer,
                              const Object* o) const = 0;
};

class NaiveScene : public Scene
{
    typedef std::forward_list<Light*> LightList;
    typedef std::forward_list<Light*>::const_iterator LightListIter;
    typedef std::forward_list<Object*> ObjectList;
    typedef std::forward_list<Object*>::const_iterator ObjectListIter;
    typedef std::forward_list<Primitive*> PrimitiveList;
    typedef std::forward_list<Primitive*>::const_iterator PrimitiveListIter;

    LightList m_lights;
    ObjectList m_objects;
    
public:

    virtual void insertLightSource(Light* l)
    {
        m_lights.push_front(l);
    }


    virtual void insertObject(Object* obj);

    virtual void removeObject(Object* obj);

    virtual Color trace(const Ray& ray, int recursionDepth);

    virtual Color computeBRDF(const Vector3& point,
                              const Vector3& normal,
                              const Ray& viewer,
                              const Object* o) const;
};

class AABBNode
{
    AABB bound;
    Object* m_pObject;

    AABBNode* left;
    AABBNode* right;

public:
    AABBNode(void):
    m_pObject(NULL),
    left(NULL),
    right(NULL)
    {
    }

    virtual ~AABBNode(void)
    {
        delete m_pObject;
        delete left;
        delete right;
    }

    Object* getObject(void)
    {
        return m_pObject;
    }

    AABBNode* getLeft(void)
    {
        return left;
    }

    AABBNode* getRight(void)
    {
        return right;
    }

    void insert(Object* pObj)
    {
        if (m_pObject == NULL) {
            m_pObject = pObj;
        } else if (left == NULL) {
            left = new AABBNode;
            left->insert(pObj);
        } else if (right == NULL) {
            right = new AABBNode;
            right->insert(pObj);
        } else {
            left->insert(pObj);
        }
    }

    void queryObject(const Ray& tracer,
                     Object* hitObject,
                     Primitive* hitPrimitive,
                     Vector3& hitPoint,
                     Vector3& hitPointNormal,
                     float& hitTime)
    {
    }
};

class AABBScene : public Scene
{
    AABBNode* m_RootNode;

    typedef std::forward_list<Light*> LightList;
    typedef std::forward_list<Light*>::const_iterator LightListIter;
    typedef std::forward_list<Object*> ObjectList;
    typedef std::forward_list<Object*>::const_iterator ObjectListIter;
    typedef std::forward_list<Primitive*> PrimitiveList;
    typedef std::forward_list<Primitive*>::const_iterator PrimitiveListIter;

    LightList m_lights;
    
public:
    virtual void insertLightSource(Light* l)
    {
        m_lights.push_front(l);
    }

    virtual void insertObject(Object* obj);

    virtual void removeObject(Object* obj);

    virtual Color trace(const Ray& ray, int recursionDepth);

    virtual Color computeBRDF(const Vector3& point,
                              const Vector3& normal,
                              const Ray& viewer,
                              const Object* o) const;
};

#endif
