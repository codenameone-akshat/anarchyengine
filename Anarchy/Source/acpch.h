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

//External Libs
#include <fmt/core.h>
#include <d3d12.h>


#ifdef ANARCHY_MATH_ENABLE
#include <Framework/Math/Math.h>
#endif // ANARCHY_MATH_ENABLE

// Types
#include <Platform/Types/Types.h>
#include <Platform/Types/NumericTypeLimits.h>

// Utils
#include <Utils/Logger/Logger.h>
#include <Utils/Time/ScopedTimer.h>
#include <Utils/StringUtils/StringUtils.h>
#include <Platform/Assertion.h>

// Helpers
#include <Framework/ClassHelpers.h>
#include <Framework/SerializationHelpers.h>
#include <Framework/FrameworkHelpers.h>
#include <Framework/MemoryHelpers.h>

#endif // !_ACPCH_H_
