#include "film.h"

void Film::commit(const Sample& sample, const Color& color)
{
    m_pBuffer[sample.j * m_width + sample.i] = color;
    m_bucketList[sample.j * m_width + sample.i].push(color);
}

void Film::flush(void)
{
    Color sampled_color;
    int samples;
    float contr = 0.0f;

    for (int i = 0; i < m_width * m_height; ++i)
    {
        sampled_color = Color(0, 0, 0);
        samples = 1;

        while (!m_bucketList[i].empty())
        {
            contr = 1.0f / samples;
            sampled_color = sampled_color.mul(1 - contr).add(m_bucketList[i].back().mul(contr));
            m_bucketList[i].pop();
            ++samples;
        }

        m_pBuffer[i] = m_pBuffer[i].add(sampled_color);
    }
}

std::vector<unsigned char> Film::getBuffer(void)
{
    std::vector<unsigned char> imageVector;

    for (int i = 0; i < m_width * m_height; ++i)
    {
        //LodePNG's origin is at top-left, while we assume screen space origin as bottom-left
        int lpIndex = (m_height - (i / m_height) - 1) * m_width + (i % m_width);
        imageVector.push_back(m_pBuffer[lpIndex].getRed() * 255);
        imageVector.push_back(m_pBuffer[lpIndex].getGreen() * 255);
        imageVector.push_back(m_pBuffer[lpIndex].getBlue() * 255);
        imageVector.push_back(255);
    }

    return imageVector;
}
