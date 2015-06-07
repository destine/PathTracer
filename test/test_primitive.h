#include "../src/primitive.h"
#include "../src/ray.h"
#include "../src/vector.h"

#include <iostream>

bool test_primitive_sphere(void)
{
    Vector3 normal;

    UnitSphere target;

    Vector3 start;
    start.set(0, 0);
    start.set(1, 1);
    start.set(2, -10);

    Vector3 end;
    end.set(0, 0);
    end.set(1, 1);
    end.set(2, 0);

    Ray shooter(start, end);

    float intersectionPoint = 0;

    bool shouldBeTrue = target.intersects(shooter, intersectionPoint, normal);

    start.set(0, 1);
    end.set(0, 1);
    shooter = Ray(start, end);

    bool shouldBeFalse = target.intersects(shooter, intersectionPoint, normal);

    return shouldBeTrue && !shouldBeFalse;
}

bool test_primitive_triangle(void)
{
    Vector3 normal;

    Vector3 vertex1;
    
    Vector3 vertex2;
    vertex2.set(0, 0);
    vertex2.set(1, 1);
    vertex2.set(2, 0);

    Vector3 vertex3;
    vertex3.set(0, 1);
    vertex3.set(1, 0);
    vertex3.set(2, 0);

    Triangle trigon(vertex1, vertex2, vertex3);

    Vector3 start;
    start.set(0, 0.25f);
    start.set(1, 0.25f);
    start.set(2, -5.0f);

    Vector3 end;
    end.set(0, 0.25f);
    end.set(1, 0.25f);
    end.set(2, 5.00f);

    Ray shooter(start, end);

    float intersectionPoint = 0;

    bool shouldBeTrue = trigon.intersects(shooter, intersectionPoint, normal);

    start.set(0, 1);
    end.set(0, 1);

    shooter = Ray(start, end);

    bool shouldBeFalse = trigon.intersects(shooter, intersectionPoint, normal);
    
    return shouldBeTrue && !shouldBeFalse;
}

bool test_primitive_multiple(void)
{
    return true;
}

/* BOOL test_transform(int testNum)
 * 
 * Runs test as specified by TESTNUM. Each test is assigned a unique numerical
 * ID. To run all tests, simply call test_transform with increasing values of
 * TESTNUM, until test_transform returns FALSE;
 *
 * return: TRUE iff testNum is valid.
 *
 * ex.
 *
 * for (int i = 0; test_transform(i); ++i);
 *
 */
bool test_primitive(int testNum, bool& success)
{
    switch (testNum)
    {
    case 0:
        std::cout << "primitive sphere: ";
        success = test_primitive_sphere();
        break;
    case 1:
        std::cout << "primitive triangle: ";
        success = test_primitive_triangle();
        break;
    case 2:
        std::cout << "primitive multiple: ";
        success = test_primitive_multiple();
        break;
    default:
        return false;
        break;
    }

    if (success)
        std::cout << "PASS\n";
    else
        std::cout << "FAIL\n";

    return true;
}