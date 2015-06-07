#ifndef __incl__light
#define __incl__light
#include <forward_list>
#include "primitive.h"
#include "object.h"
#include "color.h"

class Light
{
protected:
	typedef std::forward_list<Primitive*> PrimitiveList;
    typedef std::forward_list<Primitive*>::const_iterator PrimitiveListIter;

    Vector3 m_position;
    Color m_color;
	int m_falloff;

public:
	Light(float x, float y, float z,
		  float r, float g, float b,
		  int falloff = 0)
	{
		m_position.set(0, x);
		m_position.set(1, y);
		m_position.set(2, z);

        m_color.setRed(r);
        m_color.setGreen(g);
        m_color.setBlue(b);

		m_falloff = falloff;
	}

    Vector3 getPosition(void) const
    {
         return m_position;
    }

    Color getColor(void) const
    {
        return m_color;
    }

	virtual Ray getRayToPoint(const Vector3& point) const = 0;
	virtual bool isBlockedByObject(const Object* o, const Ray& r) const = 0;
	virtual Color colorObject(const Ray& pointToLight,
		                      const Vector3& normal,
		                      const Ray& viewer,
		                      const Object* o) const = 0;
};

class PointLight : public Light
{
public:
	PointLight(float x, float y, float z,
       		   float r, float g, float b,
		       int falloff = 0):
	Light(x, y, z, r, g, b, falloff)
	{
	}

	virtual Ray getRayToPoint(const Vector3& point) const;
	virtual bool isBlockedByObject(const Object* o, const Ray& r) const;
	virtual Color colorObject(const Ray& pointToLight, const Vector3& normal, const Ray& viewer, const Object* o) const;
};

class DirectionalLight : public Light
{
public:
	DirectionalLight(float x, float y, float z,
       		         float r, float g, float b,
		             int falloff = 0):
    Light(x, y, z, r, g, b, falloff)
    {
	}

    virtual Ray getRayToPoint(const Vector3& point) const;
	virtual bool isBlockedByObject(const Object* o, const Ray& r) const;
	virtual Color colorObject(const Ray& pointToLight, const Vector3& normal, const Ray& viewer, const Object* o) const;
};

class AmbientLight : public Light
{
public: 
	AmbientLight(float r, float g, float b):
	Light(0, 0, 0, r, g, b, 0)
	{
	}

	virtual Ray getRayToPoint(const Vector3& point) const;
	virtual bool isBlockedByObject(const Object* o, const Ray& r) const;
	virtual Color colorObject(const Ray& pointToLight, const Vector3& normal, const Ray& viewer, const Object* o) const;
};

#endif