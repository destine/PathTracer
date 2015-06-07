#ifndef __incl__raytracer
#define __incl__raytracer

#include "film.h"
#include "sampler.h"
#include "scene.h"
#include <forward_list>

#define OUTPUT_IMAGE_WIDTH 1500
#define OUTPUT_IMAGE_HEIGHT 1500

class RayTracer
{
    Film* m_film;
    Sampler* m_sampler;
    Scene* m_scene;
    Material m_material;
    Transform m_transform;

    typedef std::forward_list<Light*> LightList;
    typedef std::forward_list<Light*>::iterator LightListIter;
    typedef std::forward_list<Object*> ObjectList;
    typedef std::forward_list<Object*>::iterator ObjectListIter;
    typedef std::forward_list<Primitive*> PrimitiveList;
    typedef std::forward_list<Primitive*>::iterator PrimitiveListIter;
 
    bool m_isInitialized;

public:
    RayTracer(void) {
        m_isInitialized = false;
        m_material.set(0,0,0,0,0,0,0,0,0,0,0,0,0);
    }

    virtual ~RayTracer(void)
    {
        delete m_film;
        delete m_sampler;
        delete m_scene;
    }
    
    virtual Scene* getScene(void) {
        return m_scene;
    }

    virtual void error(int msg);

    virtual void init(FILE* config);

    virtual void run(void);

    virtual void halt(void);

    virtual void parse(char* flag, std::vector<float> v);
    
    virtual void parseObj(FILE* obj);

    virtual Film* getFilm(void) const
    {
        return m_film;
    }
};

#endif
