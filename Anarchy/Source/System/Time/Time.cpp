#include <sstream>
#include <cmath>

#include "Time.h"

namespace anarchy
{
	Time::time_point Time::g_dt = std::chrono::high_resolution_clock::now();
	uint16_t Time::g_fps = 0;

	Time::~Time()
    {
		Stop();
    }

	void Time::Stop()
	{
		g_dt = time_point();
		g_fps = 0;
	};
    void Time::OnSystemTimeStep()
    {
        m_fps = m_numFrames; //record number of frames passed in a second.
        
        m_systemTimer = 0;
        m_numFrames = 0;

        Logger::GetInstance().LogInfo(std::to_string(m_fps).c_str());
    }
}