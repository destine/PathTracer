#include <iostream>

#include "LodePNG/lodepng.h"
#include "src/raytracer.h"
#include "src/debug.h"

void usage()
{

  std::cerr << "Usage: run [filename]\n \
  File format:\n \
  [-cam ex ey ez llx lly llz lrx lry lrz ulx uly ulz urx ury urz]\n \
  [-sph cx cy cz r]\n \
  [-tri ax ay az bx by bz cx cy cz]\n \
  [-obj \"file name”]\n \
  [-ltp px py pz r g b [falloff] ]\n \
  [-ltd dx dy dz r g b]\n \
  [-lta r g b]\n \
  [-mat kar kag kab kdr kdg kdb ksr ksg ksb ksp krr krg krb]\n \
  [-xft tx ty tz]\n \
  [-xfr rx ry rz]\n \
  [-xfs sx sy sz]\n \
  \n";
  exit(1);
}

void encodeOneStep(const char* filename, std::vector<unsigned char> image, unsigned width, unsigned height)
{
    unsigned error = lodepng::encode(filename, image, width, height);

    if (error)
        std::cerr << "error encoding output!\n";
}

int main(int argc, char *argv[])
{
    signal(SIGSEGV, handler);
    FILE* pStream;
    if (argc == 1) {
      pStream = stdin;
    } else if (argc == 2 && (pStream = fopen(argv[1], "r"))) {
    } else {
      usage();
    }
    // initialization
    RayTracer app;
    app.init(pStream);
    app.run();

    // encode raytracer image
    encodeOneStep("output.png", app.getFilm()->getBuffer(), OUTPUT_IMAGE_WIDTH, OUTPUT_IMAGE_HEIGHT);

    // clean up
    app.halt();
    fclose(pStream);
    return 0;
}
