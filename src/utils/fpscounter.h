#ifndef FPS_H
#define FPS_H

#include "timer.h"

class FpsCounter
{
public:
    FpsCounter();
    float getFps() const { return m_FpsAverage; }
    void newFrame();
    void clear();
    void setSmoothing(float val);

private:
    Timer m_Timer;
    int m_FramesPerDraw;
    float m_FpsAverage;
    float m_Smoothing;
};

#endif // FPS_H
