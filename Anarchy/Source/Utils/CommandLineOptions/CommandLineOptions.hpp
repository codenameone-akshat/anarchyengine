#ifndef _COMMAND_LINE_OPTIONS_H_
#define _COMMAND_LINE_OPTIONS_H_

#include <functional>

#include "../../Framework/Includes/FrameworkAliases.h"

namespace anarchy
{
	class CommandLineOptions
	{
	public:
		CommandLineOptions() = default;
		~CommandLineOptions() = default;
	
		void Init();

		template <typename T>
		void RegisterCommandLineOption(AC_String optionString, std::function<void(T arg...)> functor);
	private:
		
	};
	
	template<typename T>
	inline void CommandLineOptions::RegisterCommandLineOption(AC_String optionString, std::function<void(T arg...)> functor)
	{
	}
}

#endif // _COMMAND_LINE_OPTIONS_H_
