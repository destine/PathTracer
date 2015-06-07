#ifndef __incl__sampler
#define __incl__sampler

#include <mutex>

class Sampler;

struct Sample
{
    int i;
    int j;
    Sampler* source;
};

class Sampler
{
    unsigned int m_width, m_height;
    int m_iter;

    std::mutex m_incr_mutex;

public:
    Sampler(int width, int height)
    {
        m_width = width;
        m_height = height;
        m_iter = 0;
    }

    virtual ~Sampler(void)
    {
    }

    bool getSample(Sample& sample)
    {
        m_incr_mutex.lock();

        sample.i = m_iter % m_width;
        sample.j = m_iter / m_height;

        sample.source = this;

        ++m_iter;

        m_incr_mutex.unlock();

        return sample.j < m_height;
    }

    unsigned int getWidth(void) const
    {
        return m_width;
    }

    unsigned int getHeight(void) const
    {
        return m_height;
    }
};

#endif
