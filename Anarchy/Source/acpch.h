#ifndef _ACPCH_H_
#define _ACPCH_H_

#include <Framework/ProjectConfig.h>

#ifdef USE_EIGEN_LIB
#include <Eigen/Dense_BoostSerialized>
#endif // USE_EIGEN_LIB

#ifdef USE_CUSTOM_MATH
#include <Framework/Math/Math.h>
#endif // USE_CUSTOM_MATH
// Types
#include <Platform/Types/Types.h>
#include <Platform/Types/NumericTypeLimits.h>

// Helpers
#include <Framework/ClassHelpers.h>
#include <Framework/SerializationHelpers.h>
#include <Framework/FrameworkHelpers.h>
#include <Framework/MemoryHelpers.h>
#include <fmt/core.h>

// Graphics
#include <d3d12.h>

// C++ Basic Types
#include <array>
#include <vector>

#endif // !_ACPCH_H_
