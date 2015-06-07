#ifndef __incl__primitive
#define __incl__primitive

#include "ray.h"

class AABB
{
    Vector3 m_minimum;
    Vector3 m_maximum;

    bool isInitialized;

public:
    AABB(void)
    {
        isInitialized = false;
    }

    AABB(const Vector3& minimum, const Vector3& maximum)
    {
        isInitialized = true;
        addPointToBox(minimum);
        addPointToBox(maximum);
    }

    void addPointToBox(const Vector3& member);

    virtual bool intersects(const Ray& test,
                            float& t_return,
                            Vector3& normal) const;

    AABB merge(const AABB& other)
    {
        AABB result;
        result.addPointToBox(m_minimum);
        result.addPointToBox(m_maximum);
        result.addPointToBox(other.m_minimum);
        result.addPointToBox(other.m_maximum);
        return result;
    }
};

class Primitive
{
public:
    virtual bool intersects(const Ray& test, float& t_return, Vector3& normal) const = 0;
    virtual AABB getBoundBox(void) const = 0;
    virtual void print(void) const = 0;
    virtual void printVector(const Vector3) const;
};

class UnitSphere : public Primitive
{

public:
    UnitSphere(void)
    {
    }

    virtual bool intersects(const Ray& test,
                            float& t_return,
                            Vector3& normal) const;

    virtual AABB getBoundBox(void) const
    {
        Vector3 lowerLeft;
        lowerLeft.set(0, -1);
        lowerLeft.set(0, -1);
        lowerLeft.set(0, -1);

        Vector3 upperRight;
        upperRight.set(0, 1);
        upperRight.set(1, 1);
        upperRight.set(2, 1);
        
        return AABB(lowerLeft, upperRight);
    }

    virtual void print(void) const;
};

class Triangle : public Primitive
{
    Vector3 m_vertexA;
    Vector3 m_vertexB;
    Vector3 m_vertexC;
    Vector3 m_normalA;
    Vector3 m_normalB;
    Vector3 m_normalC;
    Vector3 m_textureA;
    Vector3 m_textureB;
    Vector3 m_textureC;
    
public:
    Triangle(void)
    {
    }
    
    Triangle(const Vector3& point1,
             const Vector3& point2,
             const Vector3& point3)
    {
        m_vertexA = point1;
        m_vertexB = point2;
        m_vertexC = point3;
        m_normalA = (point2.sub(point1)).cross(point3.sub(point1)).normalize();
        m_normalB = m_normalA;
        m_normalC = m_normalA;
    }
    
    virtual void print(void) const;
    
    virtual void setVertices(const Vector3& vertex1,
                             const Vector3& vertex2,
                             const Vector3& vertex3)
    {
        m_vertexA = vertex1;
        m_vertexB = vertex2;
        m_vertexC = vertex3;
        m_normalA = (vertex2.sub(vertex1)).cross(vertex3.sub(vertex1)).normalize();
        m_normalB = m_normalA;
        m_normalC = m_normalA;
    }
    
    virtual void setVertex(const int index, const Vector3& v) {
        switch(index)
        {
            case 0:
                m_vertexA = v;
                break;
            case 1:
                m_vertexB = v;
                break;
            case 2:
                m_vertexC = v;
                break;
            default:
                std::cerr << "Invalid index\n";
        }
        m_normalA = (m_vertexB.sub(m_vertexA)).cross(m_vertexC.sub(m_vertexA));
        m_normalB = m_normalA;
        m_normalC = m_normalA;
        return;
    }
    
    virtual void setNormals(const Vector3& n1,
                           const Vector3& n2,
                           const Vector3& n3)
    {
        m_normalA = n1;
        m_normalB = n2;
        m_normalC = n3;
    }
    
    virtual void setNormal(const int index, const Vector3& n) {
        switch(index)
        {
            case 0:
                m_normalA = n;
                break;
            case 1:
                m_normalB = n;
                break;
            case 2:
                m_normalC = n;
                break;
            default:
                std::cerr << "Invalid index\n";
        }
        return;        
    }
    
    virtual void setTextures(const Vector3& tex1,
                            const Vector3& tex2,
                            const Vector3& tex3)
    {
        m_textureA = tex1;
        m_textureB = tex2;
        m_textureC = tex3;
    }
    
    virtual void setTexture(const int index, const Vector3& t) {
        switch(index)
        {
            case 0:
                m_textureA = t;
                break;
            case 1:
                m_textureB = t;
                break;
            case 2:
                m_textureC = t;
                break;
            default:
                std::cerr << "Invalid index\n";
        }
        return;        
    }

    virtual bool intersects(const Ray& test, float& t_return, Vector3& normal) const;

    virtual AABB getBoundBox(void) const
    {
        AABB result;
        result.addPointToBox(m_vertexA);
        result.addPointToBox(m_vertexB);
        result.addPointToBox(m_vertexC);
        return result;
    }
};

#endif
