#ifndef __incl__film
#define __incl__film

#include <queue>
#include <vector>

#include "color.h"
#include "sampler.h"

class Film
{
    Color* m_pBuffer;
    int m_width, m_height;

    std::queue<Color>* m_bucketList; 

public:
    Film(int width, int height):
    m_width(width),
    m_height(height)
    {
        m_pBuffer = new Color[width * height];
        m_bucketList = new std::queue<Color>[width * height];

        for (int i = 0; i < width * height; ++i)
        {
            m_pBuffer[i] = Color(0.0f, 0.0f, 0.0f);
            m_bucketList[i] = std::queue<Color>();
        }
    }

    virtual ~Film(void)
    {
        delete m_pBuffer;
        m_pBuffer = nullptr;
    }

    void commit(const Sample& sample, const Color& color);

    // kick the bucket.
    void flush(void);

    std::vector<unsigned char> getBuffer(void);
};

#endif
