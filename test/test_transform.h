#include "../src/transform.h"
#include "../src/vector.h"

#include <iostream>

bool test_transform_translate(void)
{
    // create vector < 0, 1, 0 >.
    Vector3 vector;
    vector.set(0, 0);
    vector.set(1, 1);
    vector.set(2, 0);

    // initialize a translation transform.
    Transform transform;
    transform.translate(1, 0, 0);

    // apply transformation.
    Vector3 result;

    result = transform.transform(vector);

    return true;
}

bool test_transform_rotate(void)
{
    Vector3 vector;
    vector.set(0, 0);
    vector.set(1, 1);
    vector.set(2, 0);

    Vector3 axis1;
    axis1.set(0, 0);
    axis1.set(1, 1);
    axis1.set(2, 0);

    Vector3 axis2;
    axis2.set(0, 0);
    axis2.set(1, 0);
    axis2.set(2, 1);

    Transform transform;
    Vector3 result;

    transform.rotate(axis1, 90);

    result = transform.transform(vector);


    transform.rotate(axis2, 90);

    result = transform.transform(vector);

    return true;
}

bool test_transform_scale(void)
{
    Vector3 vector;
    vector.set(0, 1);
    vector.set(1, 0);
    vector.set(2, 0);

    Transform transform;
    transform.scale(2, 1, 5);

    Vector3 result;

    result = transform.transform(vector);

    return true;
}

bool test_transform_normal(void)
{
    Transform transform;
    transform.scale(2, 2, 2);
    transform.translate(25, 50, 75);

    Vector3 objectNormal;
    objectNormal.set(2, 1); // positive z axis

    Vector3 worldNormal = transform.transformNormal(objectNormal);

    worldNormal = worldNormal.normalize();

    return objectNormal.get(0) == worldNormal.get(0) &&
           objectNormal.get(1) == worldNormal.get(1) &&
           objectNormal.get(2) == worldNormal.get(2);
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
bool test_transform(int testNum, bool& success)
{
    switch (testNum)
    {
    case 0:
        std::cout << "transform translate: ";
        success = test_transform_translate();
        break;
    case 1:
        std::cout << "transform rotate: ";
        success = test_transform_rotate();
        break;
    case 2:
        std::cout << "transform scale: ";
        success = test_transform_scale();
        break;
    case 3:
        std::cout << "transform normal: ";
        success = test_transform_normal();
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