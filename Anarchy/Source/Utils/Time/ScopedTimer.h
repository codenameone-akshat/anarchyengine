#ifndef _SCOPED_TIMER_H_
#define _SCOPED_TIMER_H_

#include<string>
#include<chrono>

#include"../../Framework/Includes/FrameworkAliases.h"

namespace anarchy
{
	class ScopedTimer
	{
	public:
		ScopedTimer() = delete;
		ScopedTimer(AC_String timerTag);
		~ScopedTimer();
	
	private:
		std::chrono::high_resolution_clock::time_point m_start = std::chrono::high_resolution_clock::now();
		std::chrono::high_resolution_clock::time_point m_end = std::chrono::high_resolution_clock::now();
		AC_String m_tag = "UnTagged";
	};
}

#endif // _SCOPED_TIMER_H_
