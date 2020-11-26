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
		int64_t time_duration = std::chrono::duration_cast<std::chrono::milliseconds>(m_end - m_start).count();
		string message = m_tag + " Operation took " + to_string(time_duration) + " milliseconds.";

		Logger::LogInfo(Logger::LogCategory::System, message);
	}
}
