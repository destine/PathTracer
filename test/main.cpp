#include <iostream>
#include "test_primitive.h"
#include "test_transform.h"
#include "../src/scene.h"
#include "../src/camera.h"
#include "../src/transform.h"
#include "../src/view.h"
#include "../src/raytracer.h"

void printView(RayTracer& app) {
  Scene* s = app.getScene();
  Camera c = s->getCamera();
  Transform t = c.getTransform();
  View v = c.getView();
  return;
}

int main(int argc, char** argv)
{
    /*FILE* pStream;
    if (argc == 2 && (pStream = fopen(argv[1], "r"))) {
      RayTracer app;
      app.init(pStream);

      printView(app);
      
      app.halt();
    }
    fclose(pStream);*/
    int i;
    int passCount;

    bool testPassed = true;

    for (i = 0, passCount = 0; test_transform(i, testPassed); i++)
    {
         if (testPassed)
             ++passCount;
    }

    std::cout << passCount << " of " << i << " transform tests passed.\n\n";

    for (i = 0, passCount = 0; test_primitive(i, testPassed); i++)
    {
         if (testPassed)
             ++passCount;
    }

    std::cout << passCount << " of " << i << " primitive tests passed.\n\n";
}