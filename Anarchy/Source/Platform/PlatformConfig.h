#ifndef _PLATFORM_CONFIG_H_
#define _PLATFORM_CONFIG_H_

#ifdef PLATFORM_WINDOWS
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif 

#ifndef NOMINMAX
#define NOMINMAX
#endif
#endif // PLATFORM_WINDOWS

#ifdef PLATFORM_WINDOWS
#define WINDOWS_ONLY(x) x
#else
#define WINDOWS_ONLY(x) 
#endif // PLATFORM_WINDOWS

#ifdef PLATFORM_LINUX
#define LINUX_ONLY(x) x
#else
#define LINUX_ONLY(x) 
#endif //PLATFORM_LINUX

#define USE_EIGEN_LIB

#define ANARCHY_NAMESPACE_BEGIN namespace anarchy {
#define ANARCHY_NAMESPACE_END }

#define PROJECT_PARENT_DIR_NAME "anarchyengine"

#endif // !_PLATFORM_CONFIG_H_
