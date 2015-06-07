#ifndef __incl__matrix3
#define __incl__matrix3

#include "vector.h"
#include <cstring>

class Matrix3
{
protected:
    int size;
    float pElements[3 * 3];

public:
    Matrix3(void) {
        size = 3;

        for (int i = 0; i < size * size; ++i)
        {
            pElements[i] = 0;
        }
    }

    virtual bool equals(const Matrix3& rhs) const {
        for (int i = 0; i < size * size; i++)
        {
            if (pElements[i] != rhs.pElements[i])
            {
                return false;
            }
        }
        return true;
    }
    

    virtual float get(const int row, const int col) const
    {
        return pElements[row * size + col];
    }

    virtual Vector3 getRow(const int row) const
    {
        Vector3 row_vector;

        for (int i = 0; i < size; i++) {
            row_vector.set(i, get(row, i));
        }
        return row_vector;
    }

    virtual Vector3 getCol(const int col) const {
        Vector3 col_vector;
        for (int i = 0; i < size; i++)
        {
            col_vector.set(i, get(i, col));
        }
        return col_vector;
    }

    virtual void set(const int row, const int col, const float val) {
        pElements[row * size + col] = val;
    }

    virtual void setRow(const int row, const Vector3& row_vector) {
        for (int i = 0; i < size; i++)
        {
            set(row, i, row_vector.get(i));
        }
    }

    virtual void setCol(const int col, const Vector3& col_vector) {
        for (int i = 0; i < size; i++)
        {
            set(i, col, col_vector.get(i));
        }
    }

    virtual int getSize(void) const {
        return size;
    }

    virtual Matrix3 add(const Matrix3& rhs) const {
        Matrix3 result;
        for (int i = 0; i < size; i++) {
            result.setRow(i, getRow(i).add(rhs.getRow(i)));
        }
        return result;
    }

    virtual Matrix3 sub(const Matrix3& rhs) const {
        Matrix3 result;
        for (int i = 0; i < size; i++) {
            result.setRow(i, getRow(i).sub(rhs.getRow(i)));
        }
        return result;
    }

    virtual Matrix3 mul(const float scale) const {
        Matrix3 result;
        for (int i = 0; i < size; i++) {
            result.setRow(i, getRow(i).mul(scale));
        }
        return result;
    }

    virtual Matrix3 mul(const Matrix3& rhs) const {
        Matrix3 result;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                result.set(i, j, getRow(i).dot(rhs.getCol(j)));
            }
        }
        return result;
    }

    virtual Vector3 mul(const Vector3& rhs) const {
        Vector3 result;
        for (int i = 0; i < size; i++) {
            result.set(i, getRow(i).dot(rhs));
        }
        return result;
    }

    virtual Matrix3 div(const float scale) const {
        return mul(1.0f / scale);
    }

    virtual Matrix3 transpose(void) const {
        Matrix3 result;
        for (int i = 0; i < size; i++) {
            result.setRow(i,getCol(i));
        }
        return result;
    }
};

#endif
