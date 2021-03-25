#ifndef _SCOPED_TIMER_H_
#define _SCOPED_TIMER_H_

#include<string>
#include<chrono>

#include <Utils/Time/CPUTimer.h>

namespace anarchy
{
    class ScopedTimer
    {
    public:
        ScopedTimer() = delete;
        ScopedTimer(string timerTag);
        ~ScopedTimer();
    
    private:
        CPUTimer m_timer;
    };
}

#endif // _SCOPED_TIMER_H_
