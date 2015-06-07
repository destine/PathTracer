#include "transform.h"

#include <math.h>

#define PI 3.14159265

Transform Transform::concat(const Transform& other) const
{
    Transform result;

    result.m_transformTo = m_transformTo.mul(other.m_transformTo);
    result.m_transformFrom = other.m_transformFrom.mul(m_transformFrom);

    return result;
}

Transform Transform::invert(void) const
{
    Transform result;

    result.m_transformFrom = m_transformTo;
    result.m_transformTo = m_transformFrom;

    return result;
}

void Transform::translate(const float x, const float y, const float z)
{
    Matrix4 translate;

    translate.set(0, 0, 1);
    translate.set(1, 1, 1);
    translate.set(2, 2, 1);

    Matrix4 translateInverse = translate;

    Vector4 col;

    col.set(x, y, z, 1);
    translate.setCol(3,col);
    
    col.set(-x, -y, -z, 1);
    translateInverse.setCol(3,col);

    m_transformTo = translate.mul(m_transformTo); 
    m_transformFrom = m_transformFrom.mul(translateInverse);
}

void Transform::rotate(const Vector3& axis, const float degree)
{
    Vector3 axisOfRotation = axis.normalize();

    Matrix3 base;

    base.set(0, 1, -axisOfRotation.get(2));
    base.set(0, 2, axisOfRotation.get(1));
    base.set(1, 0, axisOfRotation.get(2));
    base.set(1, 2, -axisOfRotation.get(0));
    base.set(2, 0, -axisOfRotation.get(1));
    base.set(2, 1, axisOfRotation.get(0));

    Matrix3 rotation;

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            rotation.set(i, j, axisOfRotation.get(i) * axisOfRotation.get(j));
        }
    }

    rotation = rotation.add(base.mul(sin(degree * PI / 180.0)));

    rotation = rotation.sub(base.mul(base).mul(cos(degree * PI / 180.0)));

    Matrix4 rotationHomogenized;

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            rotationHomogenized.set(i, j, rotation.get(i, j));
        }
    }

    rotationHomogenized.set(3, 3, 1);

    m_transformTo = rotationHomogenized.mul(m_transformTo);
    m_transformFrom = m_transformFrom.mul(rotationHomogenized.transpose());
}

void Transform::scale(const float x, const float y, const float z)
{
    Matrix4 scaleMatrix;

    scaleMatrix.set(0, 0, x);
    scaleMatrix.set(1, 1, y);
    scaleMatrix.set(2, 2, z);
    scaleMatrix.set(3, 3, 1);

    Matrix4 scaleInverseMatrix;

    scaleInverseMatrix.set(0, 0, 1 / x);
    scaleInverseMatrix.set(1, 1, 1 / y);
    scaleInverseMatrix.set(2, 2, 1 / z);
    scaleInverseMatrix.set(3, 3, 1);

    m_transformTo = scaleMatrix.mul(m_transformTo);
    m_transformFrom = m_transformFrom.mul(scaleInverseMatrix);
}

Ray Transform::transform(const Ray& ray) const
{
    Vector3 start = transform(ray.getStart());
    Vector3 dir = transformNormal(ray.getDirection());

    return Ray(start, start.add(dir));
}

Vector3 Transform::transform(const Vector3& vector) const
{
    Vector4 homogenized;

    homogenized.set(0, vector.get(0));
    homogenized.set(1, vector.get(1));
    homogenized.set(2, vector.get(2));
    homogenized.set(3, 1);
    
    homogenized = m_transformTo.mul(homogenized);

    Vector3 result;

    result.set(0, homogenized.get(0));
    result.set(1, homogenized.get(1));
    result.set(2, homogenized.get(2));

    return result;
}

Vector3 Transform::transformInverse(const Vector3& vector) const
{
    Vector4 homogenized;

    homogenized.set(0, vector.get(0));
    homogenized.set(1, vector.get(1));
    homogenized.set(2, vector.get(2));
    homogenized.set(3, 1);
    
    homogenized = m_transformFrom.mul(homogenized);

    Vector3 result;

    result.set(0, homogenized.get(0));
    result.set(1, homogenized.get(1));
    result.set(2, homogenized.get(2));

    return result;
}

Ray Transform::transformInverse(const Ray& ray) const
{
    Vector3 start = transformInverse(ray.getStart());
    Vector3 dir = ray.getDirection();

    Vector4 homogenized;

    homogenized.set(0, dir.get(0));
    homogenized.set(1, dir.get(1));
    homogenized.set(2, dir.get(2));
    homogenized.set(3, 0);

    homogenized = m_transformFrom.transpose().mul(homogenized);

    dir.set(0, homogenized.get(0));
    dir.set(1, homogenized.get(1));
    dir.set(2, homogenized.get(2));

    return Ray(start, start.add(dir));
}

Vector3 Transform::transformNormal(const Vector3& vector) const
{
    Vector4 homogenized;

    homogenized.set(0, vector.get(0));
    homogenized.set(1, vector.get(1));
    homogenized.set(2, vector.get(2));
    homogenized.set(3, 0);
    
    homogenized = m_transformTo.transpose().mul(homogenized);

    Vector3 result;

    result.set(0, homogenized.get(0));
    result.set(1, homogenized.get(1));
    result.set(2, homogenized.get(2));

    return result;
}