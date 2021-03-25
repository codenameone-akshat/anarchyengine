#ifndef _CPU_TIMER_H_
#define _CPU_TIMER_H_

#include <chrono>
#include <Framework/ClassHelpers.h>

namespace anarchy
{
    class CPUTimer
    {
        DECLARE_DEFAULT_CLASSMEMBERS_NO_DEFAULTCONSTRUCTIBLE(CPUTimer);
        
    public:
        explicit CPUTimer(string tag) :
            m_tag(tag)
        {}

        void Start();
        void Stop();

    private:
        std::chrono::high_resolution_clock::time_point m_start;
        std::chrono::high_resolution_clock::time_point m_end;
        string m_tag = "UnTagged";
    };
}

#endif // !_CPU_TIMER_H_
