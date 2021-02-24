#ifndef _PROFILER_H_
#define _PROFILER_H_

#ifdef USE_PIX
#include <pix3.h>
#endif // USE_PIX

namespace anarchy
{
#ifdef USE_PIX

#define PROFILE_COLOR                                                           PIX_COLOR(100,150,250)
#define CPUProfileBegin(formattedString)                                        PIXBeginEvent(PROFILE_COLOR, formattedString)
#define CPUProfileEnd()                                                         PIXEndEvent()
#define GPUCommandListProfileBegin(commandList, formattedString)                PIXBeginEvent(commandList, PROFILE_COLOR, formattedString)
#define GPUCommandQueueProfileBegin(commandQueue, formattedString)              PIXBeginEvent(commandQueue, PROFILE_COLOR, formattedString)
#define GPUCommandListProfileEnd(commandList)                                   PIXEndEvent(commandList)
#define GPUCommandQueueProfileEnd(commandQueue)                                 PIXEndEvent(commandQueue)

#define ScopedCPUProfile(formattedString)                                       PIXScopedEvent(PROFILE_COLOR, formattedString)
#define ScopedGPUCommandListProfile(commandList, formattedString)               PIXScopedEvent(commandList, PROFILE_COLOR, formattedString)
#define ScopedGPUCommandQueueProfile(commandQueue, formattedString)             PIXScopedEvent(commandQueue, PROFILE_COLOR, formattedString)

#else

#define PROFILE_COLOR
#define CPUProfileBegin(formattedString)
#define CPUProfileEnd()
#define GPUCommandListProfileBegin(commandList, formattedString)
#define GPUCommandQueueProfileBegin(commandQueue, formattedString)
#define GPUCommandListProfileEnd(commandlist)
#define GPUCommandQueueProfileEnd(commandQueue)

#define ScopedCPUProfile(formattedString)
#define ScopedGPUCommandListProfile(commandList, formattedString)
#define ScopedGPUCommandQueueProfile(commandQueue, formattedString)

#endif // USE_PIX
}

#endif // !_PROFILER_H_

