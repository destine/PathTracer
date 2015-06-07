#include "raytracer.h"
#include "primitive.h"
#include "camera.h"
#include "ray.h"
#include "light.h"
#include <vector>
#include <cstring>
#include <stdexcept>
#include <thread>

#define MAX_LINE_LENGTH 200

#define RECURSION_DEPTH 1

void RayTracer::error(int msg) {
    if (msg == 0) {
        std::cerr << "Warning: insufficient number of arguments\n";
        exit(1);
    } else if (msg == 1) {
        std::cerr << "Warning: extra arguments ignored.\n";
    }
}

void printVector(const Vector3& v) {
  std::cout << "(" << v.get(0) << ", " << v.get(1) << ", " << v.get(2) << ")" << std::endl;
}

void RayTracer::parse(char* flag, std::vector<float> v) {
    if (!flag) return;
    
    //!strcmp(arg1,arg2) returns 0 if strings arg1 and arg2 are equal
    if (!strcmp(flag, "cam")) {
        if (v.size() < 15) error(0);
        if (v.size() > 15) error(1);
        Camera camera;
        Transform cameraTransform;
        cameraTransform.translate(v[0], v[1], v[2]);
        camera.setTransform(m_transform.concat(cameraTransform));
        Vector3 ll,lr,ul,ur;
        ll.set(v[3], v[4], v[5]);
        lr.set(v[6], v[7], v[8]);
        ul.set(v[9], v[10], v[11]);
        ur.set(v[12], v[13], v[14]);
        View view(ll,lr,ul,ur);
        camera.setView(view);
        m_scene->setCamera(camera);
    } else if (!strcmp(flag, "sph")) {
        if (v.size() < 4) error(0);
        if (v.size() > 4) error(1);
        Object* o = new Object();
        UnitSphere* u = new UnitSphere();
        o->appendPrimitive(u);
        Transform sphereTransform;
        sphereTransform.scale(v[3], v[3], v[3]);
        sphereTransform.translate(v[0],v[1],v[2]);
        o->setTransform(m_transform.concat(sphereTransform));
        o->setMaterial(m_material);
        m_scene->insertObject(o);
    } else if (!strcmp(flag, "tri")) {
        if (v.size() < 9) error(0);
        if (v.size() > 9) error(1);
        Object* o = new Object();
        Vector3 p1, p2, p3;
        p1.set(v[0], v[1], v[2]);
        p2.set(v[3], v[4], v[5]);
        p3.set(v[6], v[7], v[8]);
        Triangle* t = new Triangle(p1, p2, p3);
        o->appendPrimitive(t);
        o->setTransform(m_transform);
        o->setMaterial(m_material);
        m_scene->insertObject(o);
    } else if (!strcmp(flag, "ltp")) {
        if (v.size() < 6) error(0);
        if (v.size() > 7) error(1);
        int falloff = 0;
        if (v.size() == 7) falloff = v[6];
        PointLight* pl = new PointLight(v[0], v[1], v[2], v[3], v[4], v[5], falloff);
        m_scene->insertLightSource(pl);
    } else if (!strcmp(flag, "ltd")) {
        if (v.size() < 6) error(0);
        if (v.size() > 6) error(1);
        DirectionalLight* dl = new DirectionalLight(v[0], v[1], v[2], v[3], v[4], v[5]);
        m_scene->insertLightSource(dl);
    } else if (!strcmp(flag, "lta")) {
        if (v.size() < 3) error(0);
        if (v.size() > 3) error(1);
        AmbientLight* al = new AmbientLight(v[0], v[1], v[2]);
        m_scene->insertLightSource(al);
    } else if (!strcmp(flag, "mat")) {
        if (v.size() < 13) error(0);
        if (v.size() > 13) error(1);
        Material m;
        m_material.set(v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7], v[8], v[9], v[10], v[11], v[12]);
    } else if (!strcmp(flag, "xft")) {
        if (v.size() < 3) error(0);
        if (v.size() > 3) error(1);
        Transform t;
        t.translate(v[0], v[1], v[2]);
        m_transform = m_transform.concat(t);
    } else if (!strcmp(flag, "xfr")) {
        if (v.size() < 3) error(0);
        if (v.size() > 3) error(1);
        Vector3 axis;
        axis.set(v[0], v[1], v[2]);
        int degree = sqrtf(axis.getSquaredLength());
        axis = axis.normalize();
        Transform t;
        t.rotate(axis, degree);
        m_transform = m_transform.concat(t);
    } else if (!strcmp(flag, "xfs")) {
        if (v.size() < 3) error(0);
        if (v.size() > 3) error(1);
        Transform t;
        t.scale(v[0], v[1], v[2]);
        m_transform = m_transform.concat(t);
    } else if (!strcmp(flag, "xfz\n") || !strcmp(flag, "xfz")) {
        if (v.size() > 0) error(1);
        m_transform = Transform();
    }
    
    return;
}

void RayTracer::parseObj(FILE* obj) {
  //Remember: vector is 1-indexed
    std::vector<Vector3> vertices, textures, normals;
    char pFileLine[MAX_LINE_LENGTH];
    Object* o = new Object();
    //Looping through lines
    while(fgets(pFileLine, MAX_LINE_LENGTH, obj) != NULL) {
        char* tok = strtok(pFileLine, " ");
        if (!strcmp(tok, "f")) {
            Triangle* t = new Triangle();
            int vertexIndex = 0;
            char *vertexStrings[3];
        
            //Storing vertex strings
            while ((tok = strtok(NULL, " ")) != NULL) {
                if (vertexIndex > 2) error(1);
                vertexStrings[vertexIndex] = tok;
                vertexIndex++;
            }
            if (vertexIndex < 3) error(0);
            
            //Looping through vertices
            for (int i = 0; i < 3; i++) {
                char* subtok = strtok(vertexStrings[i], "/ ");
                t->setVertex(i, vertices[std::stoi(subtok)-1]);
                int argIndex = 1;
                //Looping through arguments v1/[vt]/[vn]
                while ((subtok = strtok(NULL, "/ ")) != NULL) {
                    if (argIndex == 1) {
                        t->setTexture(i, textures[std::stof(subtok)-1]);
                    } else if (argIndex == 2) {
                        t->setNormal(i, normals[std::stof(subtok)-1]);
                    } else {
                        error(1);
                    }
                    argIndex++;
                }
            }
            o->appendPrimitive(t);
            o->setTransform(m_transform);
            o->setMaterial(m_material);
        } else if (!strcmp(tok,"\n") || !strcmp(tok,"")) {
        } else {
            char flag[strlen(tok)];
            strcpy(flag, tok);
            Vector3 v;
            int index = 0;
            bool validLine = true;
            
            while ((tok = strtok(NULL, " ")) != NULL) {
                if (index > 2) error(1);
                try {
                    v.set(index, std::stof(tok));
                    index++;
                } catch (const std::invalid_argument& exception) {
                    validLine = false;
                    break;
                }
            }
        
            if (validLine) {
                if (index < 2) error(0);
                
                if (!strcmp(flag, "v")) {
                    vertices.push_back(v);
                } else if (!strcmp(flag, "vt")) {
                    textures.push_back(v);
                } else if (!strcmp(flag, "vn")) {
                    normals.push_back(v);
                }
            }
        }
    }
    m_scene->insertObject(o);
    return;
}

void RayTracer::init(FILE* config)
{
    m_scene = new NaiveScene;
    m_sampler = new Sampler(OUTPUT_IMAGE_WIDTH,OUTPUT_IMAGE_HEIGHT);
    m_film = new Film(OUTPUT_IMAGE_WIDTH,OUTPUT_IMAGE_HEIGHT);

    char pFileLine[MAX_LINE_LENGTH];

    while (fgets(pFileLine, MAX_LINE_LENGTH, config) != NULL)
    {
        char* tok = strtok(pFileLine, " ");

        char flag[strlen(tok)];
        strcpy(flag, tok);
        if (!strcmp(flag, "obj")) {
            tok = strtok(NULL, " ");
            FILE* obj;
            if (tok != NULL) {
                obj = fopen("input.obj", "r");          
                if (obj == NULL) {
                    std::cout << "ERROR: Bad file name\n";
                    exit(1);
                }
                parseObj(obj);
            } else {
                error(0);
            }
            fclose(obj);
            tok = strtok(NULL, " ");
            if (tok != NULL) {
                error(1);
            }
        } else {
            std::vector<float> args;
            while((tok = strtok(NULL, " ")) != NULL)
            {
                try {
                    args.push_back(std::stof(tok));
                } catch (const std::invalid_argument& exception) {
                    break;
                }
            }
            parse(flag, args);
        }

      memset(pFileLine, 0, MAX_LINE_LENGTH);
    }

    m_isInitialized = true;
}

void _trace(Scene* m_scene, Sampler* m_sampler, Film* m_film)
{
    Color color;
    Sample sample;
    Ray ray;

    while (m_sampler->getSample(sample))
    {
        ray = m_scene->getCamera().generateRay(sample);
        color = m_scene->trace(ray, RECURSION_DEPTH);
        m_film->commit(sample, color);
    }
}

void RayTracer::run(void)
{
    if (m_isInitialized == false) {
        exit(1);
    }
/*
    Color color;
    Sample sample;
    Ray ray;

    float loops = OUTPUT_IMAGE_WIDTH*OUTPUT_IMAGE_HEIGHT;
    float loop = 0;
    while (m_sampler->getSample(sample))
    {
        if ((int)loop % 10000 == 0) {
            int percent = 100*loop/loops;
            printf("%3d%% [", percent);
            for (int i = 0; i < percent; i++) {
                printf("=");
            }
            for (int i = 0; i < (100-percent); i++) {
                printf(" ");
            }
            printf("]\n\033[F\033[J");
        }
        ray = m_scene->getCamera().generateRay(sample);
        color = m_scene->trace(ray, RECURSION_DEPTH);
        m_film->commit(sample, color);
        loop++;
    } */

        const int THREAD_COUNT = 7;
        std::thread* threads[THREAD_COUNT];

        for (int i = 0; i < THREAD_COUNT; ++i)
        {
            threads[i] = new std::thread(_trace, m_scene, m_sampler, m_film);
        }

        for (int i = 0; i < THREAD_COUNT; ++i)
        {
            threads[i]->join();
            delete threads[i];
        }

    m_film->flush();
}

void RayTracer::halt(void)
{
}
