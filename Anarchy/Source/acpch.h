#ifndef _ACPCH_H_
#define _ACPCH_H_

#include <Framework/ProjectConfig.h>

// C++ Basic Types
#include <array>
#include <vector>
#include <type_traits>
#include <memory>

// C++ Math
#include <cmath>

#ifdef PLATFORM_WINDOWS
#include <wrl.h>
#endif // PLATFORM_WINDOWS

#ifdef ANARCHY_MATH_ENABLE
#include <Framework/Math/Math.h>
#endif // ANARCHY_MATH_ENABLE

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

#endif // !_ACPCH_H_
