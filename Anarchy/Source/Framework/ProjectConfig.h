#ifndef _PROJECT_CONFIG_H_
#define _PROJECT_CONFIG_H_

#ifdef AC_DEBUG
#define AC_DEBUGONLY(x) x
#else
#define AC_DEBUGONLY(x)
#endif // AC_DEBUG

#define USE_EIGEN_LIB

#endif // !_PROJECT_CONFIG_H_
