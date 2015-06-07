#include "primitive.h"

#define EPSILON 0.000001

bool Primitive::intersects(const Ray& ray, float& t_return, Vector3& normal) const
{
    return false;
}

bool isPointInBox(int x, int y, int llx, int lly, int urx, int ury)
{
    return llx <= x && x <= urx && lly <= y && y <= ury;
}

void AABB::addPointToBox(const Vector3& member)
{
    if (!isInitialized)
    {
        m_minimum = m_maximum = member;
        isInitialized = true;
        return;
    }

    float x = member.get(0);
    float y = member.get(1);
    float z = member.get(2);

    if (x < m_minimum.get(0))
        m_minimum.set(0, x);
    if (x > m_maximum.get(0))
        m_maximum.set(0, x);

    if (y < m_minimum.get(1))
        m_minimum.set(1, y);
    if (y > m_maximum.get(1))
        m_maximum.set(1, y);

    if (z < m_minimum.get(2))
        m_minimum.set(2, z);
    if (z > m_maximum.get(2))
        m_maximum.set(2, z);
}

bool AABB::intersects(const Ray& ray, float& t_return, Vector3& normal) const
{
    Vector3 start = ray.getStart();
    Vector3 end = ray.getEnd();

    Vector3 t_min = m_minimum.sub(start);
    t_min.set(0, t_min.get(0) / end.get(0));
    t_min.set(1, t_min.get(1) / end.get(1));
    t_min.set(2, t_min.get(2) / end.get(2));

    Vector3 t_max = m_maximum.sub(start);
    t_max.set(0, t_max.get(0) / end.get(0));
    t_max.set(1, t_max.get(1) / end.get(1));
    t_max.set(2, t_max.get(2) / end.get(2));

    Vector3 intersect;
    bool intersectionFound = false;

    // Test X Planes
    intersect = ray.getPoint(t_min.get(0));

    if (isPointInBox(intersect.get(1), intersect.get(2),
                     m_minimum.get(1), m_minimum.get(2),
                     m_maximum.get(1), m_maximum.get(2)))
    {
        intersectionFound = true;
        t_return = t_min.get(0);
        normal.set(0, -1);
        normal.set(1, 0);
        normal.set(2, 0);
    }

    intersect = ray.getPoint(t_max.get(0));

    if (isPointInBox(intersect.get(1), intersect.get(2),
                     m_minimum.get(1), m_minimum.get(2),
                     m_maximum.get(1), m_maximum.get(2)))
    {
        intersectionFound = true;
        t_return = t_max.get(0);
        normal.set(0, 1);
        normal.set(1, 0);
        normal.set(2, 0);
    }

    // test Y Planes
    intersect = ray.getPoint(t_min.get(1));

    if (isPointInBox(intersect.get(0), intersect.get(2),
                     m_minimum.get(0), m_minimum.get(2),
                     m_maximum.get(0), m_maximum.get(2)))
    {
        intersectionFound = true;
        t_return = t_min.get(1);
        normal.set(0, 0);
        normal.set(1, -1);
        normal.set(2, 0);
    }

    intersect = ray.getPoint(t_max.get(1));

    if (isPointInBox(intersect.get(0), intersect.get(2),
                     m_minimum.get(0), m_minimum.get(2),
                     m_maximum.get(0), m_maximum.get(2)))
    {
        intersectionFound = true;
        t_return = t_max.get(1);
        normal.set(0, 0);
        normal.set(1, 1);
        normal.set(2, 0);
    }

    // test Z Planes
    intersect = ray.getPoint(t_min.get(2));

    if (isPointInBox(intersect.get(0), intersect.get(1),
                     m_minimum.get(0), m_minimum.get(1),
                     m_maximum.get(0), m_maximum.get(1)))
    {
        intersectionFound = true;
        t_return = t_min.get(2);
        normal.set(0, 0);
        normal.set(1, 0);
        normal.set(2, -1);
    }

    intersect = ray.getPoint(t_max.get(2));

    if (isPointInBox(intersect.get(0), intersect.get(1),
                     m_minimum.get(0), m_minimum.get(1),
                     m_maximum.get(0), m_maximum.get(1)))
    {
        intersectionFound = true;
        t_return = t_max.get(2);
        normal.set(0, 0);
        normal.set(1, 0);
        normal.set(2, 1);
    }

    return intersectionFound;
}

bool UnitSphere::intersects(const Ray& ray, float& t_return, Vector3& normal) const
{
    float a = ray.getDirection().getSquaredLength();
    float b = 2 * ray.getDirection().dot(ray.getStart());
    float c = ray.getStart().getSquaredLength() - 1;

    if (a == 0 || 4 * a * c > b * b)
        return false;

    t_return = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
    normal = ray.getPoint(t_return);

    return true;
}

bool Triangle::intersects(const Ray& ray, float& t_return, Vector3& normal) const
{
    Vector3 edgeAB = m_vertexB.sub(m_vertexA);
    Vector3 edgeAC = m_vertexC.sub(m_vertexA);

    float det, inv_det, u, v = 0;

    Vector3 p = ray.getDirection().cross(edgeAC);

    det = edgeAB.dot(p);

    if (det > -EPSILON && det < EPSILON)
        return false;

    inv_det = 1.0f / det;

    Vector3 t = ray.getStart().sub(m_vertexA);

    u = t.dot(p) * inv_det;
    if (u < 0.0f || u > 1.0f) return false;

    Vector3 q = t.cross(edgeAB);

    v = ray.getDirection().dot(q) * inv_det;

    if (v < 0.0f || u + v > 1.0f)
        return false;

    t_return = edgeAC.dot(q) * inv_det;

    normal = m_normalA;

    return true;
}

void Primitive::printVector (const Vector3 v) const {
    std::cout << "(" << v.get(0) << ", " << v.get(1) << ", " << v.get(2) << ")\n";
    return;
}

void UnitSphere::print(void) const
{
    std::cout << "Sphere (no transforms are applied) \n";
    return;
}

void Triangle::print(void) const
{
    std::cout << "Triangle\n";
    std::cout << "Vertex A and normal: \n";
    printVector(m_vertexA);
    printVector(m_normalA);
    std::cout << "Vertex B and normal: \n";
    printVector(m_vertexB);
    printVector(m_normalB);
    std::cout << "Vertex C and normal: \n";
    printVector(m_vertexC);
    printVector(m_normalC);
    std::cout << "Texture coordinates: \n";
    printVector(m_textureA);
    printVector(m_textureB);
    printVector(m_textureC);
    return;
}