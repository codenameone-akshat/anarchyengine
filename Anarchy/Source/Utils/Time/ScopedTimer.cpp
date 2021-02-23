#include "acpch.h"

#include "ScopedTimer.h"
#include "Utils/StringUtils/StringUtils.h"
#include "Utils/Logger/Logger.h"

namespace anarchy
{	
    ScopedTimer::ScopedTimer(string timerTag)
        :m_tag(timerTag)
    {
    }
    
    ScopedTimer::~ScopedTimer()
    {
        m_end = std::chrono::high_resolution_clock::now();
        int64 time_duration = std::chrono::duration_cast<std::chrono::milliseconds>(m_end - m_start).count();
        
        int64 milliseconds = time_duration;
        int64 seconds = 0;
        int64 minutes = 0;
        string message = m_tag + fmt::format(" Operation took {} miliseconds.", milliseconds);

        if (time_duration > 1000)
        {
            seconds = milliseconds / 1000;
            milliseconds = milliseconds % 1000;
            message = m_tag + fmt::format(" Operation took {} seconds {} miliseconds.", seconds, milliseconds);
        }
        if (seconds > 60)
        {
            minutes = seconds / 60;
            seconds = time_duration % 60;
            message = m_tag + fmt::format(" Operation took {} minutes {} seconds.", minutes, seconds);
        }

        Logger::LogInfo(Logger::LogCategory::System, message);
    }
}
