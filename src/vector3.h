#ifndef __incl__vec3
#define __incl__vec3

#include <utility>
#include <iostream>
#include <cmath>

#include <stdarg.h>
#include <x86intrin.h>

class Vector3
{
protected:
    int size;
    float pComponents[3];
    
public:
    Vector3(void)
    {
        size = 3;

        for (int i = 0; i < size; ++i)
        {
            pComponents[i] = 0;
        }
    }

    virtual bool equals(Vector3 rhs) const
    {
        for (int i = 0; i < size; ++i)
        {
            if (pComponents[i] != rhs.pComponents[i])
            {
                return false;
            }
        }

        return true;
    }

    virtual float get(const int index) const
    {
        return pComponents[index];
    }
    
    virtual void set(const int index, const float val)
    {
        pComponents[index] = val;
    }

    virtual void set(const float i, const float j, const float k)
    {
        set(0, i);
        set(1, j);
        set(2, k);
    }

    virtual int getSize(void) const
    {
        return size;
    }

    virtual float getSquaredLength(void) const
    {
        float length_squared = 0;
    
        for (int i = 0; i < size; ++i)
        {
            length_squared += pComponents[i] * pComponents[i];
        }
    
        return length_squared;
    }

    virtual Vector3 add(const Vector3& other) const
    {
        Vector3 result;
        
        for (int i = 0; i < size; ++i)
        {
            result.set(i, get(i) + other.get(i));
        }
        
        return result;
    }

    virtual Vector3 sub(const Vector3& other) const
    {
         Vector3 result;
        
        for (int i = 0; i < size; ++i)
        {
            result.set(i, get(i) - other.get(i));
        }
        
        return result;
     }

    virtual Vector3 mul(const float scale) const
    {
        Vector3 result;
        
        for (int i = 0; i < size; ++i)
        {
            result.set(i, get(i) * scale);
        }
        
        return result;
    }

    virtual Vector3 div(const float scale) const
    {
        Vector3 result;

        for (int i = 0; i < size; ++i)
        {
            result.set(i, get(i) / scale);
        }

        return result;
    }

    virtual float dot(const Vector3& other) const
    {
        float result = 0.0f;

        for (int i = 0; i < size; ++i)
        {
            result += get(i) * other.get(i);
        }

        return result;
    }

    virtual Vector3 cross(const Vector3& other) const
    {
        Vector3 result;

        result.set(0, get(1) * other.get(2) - get(2) * other.get(1));
        result.set(1, get(2) * other.get(0) - get(0) * other.get(2));
        result.set(2, get(0) * other.get(1) - get(1) * other.get(0));
        
        return result;
    }

    virtual Vector3 normalize(void) const
    {
        Vector3 result;
        float length = sqrtf(getSquaredLength());

        result = div(length);

        return result;
    }
};

#endif
