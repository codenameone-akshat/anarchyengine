#include "ScopedTimer.h"
#include "Framework/Includes/FrameworkGlobals.h"
#include "Utils/Logger/Logger.h"

namespace anarchy
{	
	ScopedTimer::ScopedTimer(AC_String timerTag)
		:m_tag(timerTag)
	{
	}
	
	ScopedTimer::~ScopedTimer()
	{
		m_end = std::chrono::high_resolution_clock::now();
		int64_t time_duration = std::chrono::duration_cast<std::chrono::milliseconds>(m_end - m_start).count();
		AC_String message = m_tag + " Operation took " + AC_To_String(time_duration) + " milliseconds.";

		Logger::LogInfo(Logger::LogCategory::System, message);
	}
}
