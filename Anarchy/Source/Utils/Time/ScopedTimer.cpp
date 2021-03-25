#include "acpch.h"

#include "ScopedTimer.h"
#include "Utils/StringUtils/StringUtils.h"
#include "Utils/Logger/Logger.h"

namespace anarchy
{	
    ScopedTimer::ScopedTimer(string timerTag)
        :m_timer(timerTag)
    {
        m_timer.Start();
    }
    
    ScopedTimer::~ScopedTimer()
    {
        m_timer.Stop();
    }
}
