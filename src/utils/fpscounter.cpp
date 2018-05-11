#include "fpscounter.h"
#include "graphics/graphics.h"

#include <iostream>

FpsCounter::FpsCounter()
    : m_FramesPerDraw(0),
      m_FpsAverage((int)Graphics::s_FPS),
      m_Smoothing(0.2f)
{
    m_Timer.start();
}

void FpsCounter::newFrame()
{
    m_FramesPerDraw++;
    if(m_Timer.getTicks() >= 1000)
    {
        m_FpsAverage  = (m_FpsAverage * m_Smoothing)
                + (m_FramesPerDraw * (1.0-m_Smoothing));

        m_FramesPerDraw = 0;
        m_Timer.restart();
    }
}

void FpsCounter::clear()
{
    m_FramesPerDraw = 0;
    m_FpsAverage = 0.0f;
}

void FpsCounter::setSmoothing(float val)
{
    if (val > 0.0f && val < 1.0f)
        m_Smoothing = val;
    else
    {
        std::cout << "Fps Error: Can't set smoothing value: "
                  << val << std::endl;
    }
}
