#ifndef __incl__vec4
#define __incl__vec4

#include <utility>
#include <iostream>
#include <cmath>

#include <stdarg.h>
#include <x86intrin.h>

class Vector4
{
protected:
    int size;
    float pComponents[4];

public:
    Vector4(void)
    {
        size = 4;

        for (int i = 0; i < size; ++i)
        {
            pComponents[i] = 0;
        }
    }

    virtual bool equals(Vector4 rhs) const
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

    virtual void set(const float i, const float j, const float k, const float l)
    {
        set(0, i);
        set(1, j);
        set(2, k);
        set(3, l);
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

    virtual Vector4 add(const Vector4& other) const
    {
        Vector4 result;
        
        __m128 a = _mm_load_ps(pComponents);
        __m128 b = _mm_load_ps(other.pComponents);
        __m128 c = _mm_add_ps(a, b);

        _mm_store_ps(result.pComponents, c);

        return result;
    }

    virtual Vector4 sub(const Vector4& other) const
    {
        Vector4 result;
        
        __m128 a = _mm_load_ps(pComponents);
        __m128 b = _mm_load_ps(other.pComponents);
        __m128 c = _mm_add_ps(a, b);

        _mm_store_ps(result.pComponents, c);

        return result;
    }

    virtual Vector4 mul(const float scale) const
    {
        Vector4 result;
        
        for (int i = 0; i < size; ++i)
        {
            result.set(i, get(i) * scale);
        }
        
        return result;
    }

    virtual Vector4 div(const float scale) const
    {
        Vector4 result;

        for (int i = 0; i < size; ++i)
        {
            result.set(i, get(i) / scale);
        }

        return result;
    }

    virtual float dot(const Vector4& other) const
    {
        float result = 0.0f;

        for (int i = 0; i < size; ++i)
        {
            result += get(i) * other.get(i);
        }

        return result;
    }

    virtual Vector4 cross(const Vector4& other) const
    {
        Vector4 result;

        result.set(0, get(1) * other.get(2) - get(2) * other.get(1));
        result.set(1, get(2) * other.get(0) - get(0) * other.get(2));
        result.set(2, get(0) * other.get(1) - get(1) * other.get(0));
        
        return result;
    }

    virtual Vector4 normalize(void) const
    {
        Vector4 result;
        float length = sqrtf(getSquaredLength());

        result = div(length);

        return result;
    }
};

#endif
