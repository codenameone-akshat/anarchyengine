#ifndef _PLATFORM_LINUX_H_
#define _PLATFORM_LINUX_H_

#include "Platform/Types/Types.h"

anarchy::int32 main(anarchy::int32 argc, char** argv)
{
	using namespace anarchy;

	const string commandLine(*argv);
	// pass it to main params or whatever
	
	// TODO: Find the source dir somehow

	anarchyMain(argc, argv);
}

#endif // !_PLATFORM_LINUX_H_
