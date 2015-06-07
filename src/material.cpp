#include <iostream>
#include "material.h"
using namespace std;


void Material::set(float ar, float ag, float ab,
                   float dr, float dg, float db,
                   float sr, float sg, float sb, float sp,
                   float rr, float rg, float rb)
{
    ambient = Color(ar, ag, ab);
    diffuse = Color(dr, dg, db);
    specular = Color(sr, sg, sb);
    reflective = Color(rr,rg,rb);

    power = sp;
}
