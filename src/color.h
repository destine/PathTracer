#ifndef __incl__color
#define __incl__color

class Color
{
    float red;
    float green;
    float blue;

public:
    Color(void)
    {
        red = 0;
        green = 0;
        blue = 0;
    }

    Color(float r, float g, float b)
    {
        red = r;
        green = g;
        blue = b;
    }

    Color(const Color& another)
    {
        red = another.red;
        green = another.green;
        blue = another.blue;
    }

    float getRed(void) const;
    float getGreen(void) const;
    float getBlue(void) const;
    void setRed(float r);
    void setGreen(float g);
    void setBlue(float b);

    Color add(const Color& other) const;
    Color sub(const Color& other) const;
    Color mul(const Color& other) const;
    Color mul(const float s) const;
    Color div(const float s) const;
};

#endif