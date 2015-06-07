#include "color.h"

#include <iostream>

float Color::getRed(void) const {
    return red;
}
float Color::getGreen(void) const {
    return green;
}
float Color::getBlue(void) const {
    return blue;
}

void Color::setRed(float r) {
    if (r < 0.0 || r > 1.0) {
        std::cerr << "R value must be between 0.0 and 1.0\n";
        exit(1);
    } else {
        red = r;
    }
}

void Color::setGreen(float g) {
    if (g < 0.0 || g > 1.0) {
        std::cerr << "G value must be between 0.0 and 1.0\n";
        exit(1);
    } else {
        green = g;
    }
}

void Color::setBlue(float b) {
    if (b < 0.0 || b > 1.0) {
        std::cerr << "B value must be between 0.0 and 1.0\n";
        exit(1);
    } else {
        blue = b;
    }
}

Color Color::add(const Color& other) const
{
    Color result;
    result.red = std::min(1.0f,red+other.getRed());
    result.green = std::min(1.0f,green+other.getGreen());
    result.blue = std::min(1.0f,blue+other.getBlue());

    return result;
}

Color Color::sub(const Color& other) const
{
    Color result;
    result.red = std::max(0.0f,red-other.getRed());
    result.green = std::max(0.0f,green-other.getGreen());
    result.blue = std::max(0.0f,blue-other.getBlue());

    return result;
}

Color Color::mul(const Color& other) const
{
    Color result;
    result.red = std::min(1.0f,red*other.getRed());
    result.green = std::min(1.0f,green*other.getGreen());
    result.blue = std::min(1.0f,blue*other.getBlue());

    return result;
}

Color Color::mul(const float s) const
{
    Color result;
    result.red = std::min(1.0f, red*s);
    result.green = std::min(1.0f, green*s);
    result.blue = std::min(1.0f,blue*s);

    return result;
}

Color Color::div(const float s) const
{
    Color result;

    if (s == 0.0)
    {
        std::cerr << "Cannot divide by 0.0\n";
        exit(1);
    }
    else
    {
        result.red = std::max(0.0f, red/s);
        result.green = std::max(0.0f, green/s);
        result.blue = std::max(0.0f, blue/s);
    }

    return result;
}