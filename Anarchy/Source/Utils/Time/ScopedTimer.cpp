#include "ScopedTimer.h"
#include "../Logger/Logger.h"
#include "../../Framework/Includes/FrameworkGlobals.h"

namespace anarchy::utils
{	
	ScopedTimer::ScopedTimer(framework::AC_String timerTag)
		:m_tag(timerTag)
	{
	}
	
	ScopedTimer::~ScopedTimer()
	{
		m_end = std::chrono::high_resolution_clock::now();
		int64_t time_duration = std::chrono::duration_cast<std::chrono::milliseconds>(m_end - m_start).count();
		framework::AC_String message = m_tag + " Operation took " + framework::AC_To_String(time_duration) + " milliseconds.";

		Logger::LogInfo(Logger::LogCategory::System, message);
	}
}
