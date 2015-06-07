#ifndef __incl__material
#define __incl__material

#include "color.h"

class Material
{
	Color ambient;
	Color diffuse;
	Color specular;
	Color reflective;

	float power;

public:

	Material(void)
	{
	}

    Color getAmbient(void) const
    {
    	return ambient;
    }

    Color getDiffuse(void) const
    {
    	return diffuse;
    }

    Color getSpecular(void) const
    {
    	return specular;
    }

    float getPower(void) const
    {
    	return power;
    }
    
    Color getReflective(void) const
    {
    	return reflective;
    }

	void set(float ar, float ag, float ab,
	         float dr, float dg, float db,
	         float sr, float sg, float sb, float sp,
	         float rr,float rg,float rb);
};

#endif