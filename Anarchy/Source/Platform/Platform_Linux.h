#ifndef _PLATFORM_LINUX_H_
#define _PLATFORM_LINUX_H_

#include "Platform/Types/Types.h"

extern anarchy::int32 anarchyMain(anarchy::int32 argc, const anarchy::string argv); // cannot link even after the actual definition is right above in MainEngine.cpp

anarchy::int32 main(anarchy::int32 argc, char** argv)
{
	using namespace anarchy;

	const string commandLine(*argv);
	// pass it to main params or whatever
	
	// TODO: Find the source dir somehow

	anarchyMain(argc, commandLine);
}

#endif // !_PLATFORM_LINUX_H_
