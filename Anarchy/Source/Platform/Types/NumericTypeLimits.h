#ifndef _NUMERIC_TYPE_LIMITS_H_
#define _NUMERIC_TYPE_LIMITS_H_

#include <limits>
#include "Platform/Types/Types.h"

namespace anarchy
{
	template <typename T> 
	using limits = std::numeric_limits<T>;

	// byte
	auto constexpr byte_min				= limits<byte>::min();
	
	auto constexpr byte_max				= limits<byte>::max();
	
	// unsigned int
	auto constexpr uint8_min			= limits<uint8>::min();
	auto constexpr uint16_min			= limits<uint16>::min();
	auto constexpr uint32_min			= limits<uint32>::min();
	auto constexpr uint64_min			= limits<uint64>::min();
	
	auto constexpr uint8_max			= limits<uint8>::max();
	auto constexpr uint16_max			= limits<uint16>::max();
	auto constexpr uint32_max			= limits<uint32>::max();
	auto constexpr uint64_max			= limits<uint64>::max();

	// signed int			  
	auto constexpr int8_min				= limits<int8>::min();
	auto constexpr int16_min			= limits<int16>::min();
	auto constexpr int32_min			= limits<int32>::min();
	auto constexpr int64_min			= limits<int64>::min();
	
	auto constexpr int8_max				= limits<int8>::max();
	auto constexpr int16_max			= limits<int16>::max();
	auto constexpr int32_max			= limits<int32>::max();
	auto constexpr int64_max			= limits<int64>::max();
	
	// floating point
	auto constexpr float32_min			= limits<float32>::min();
	auto constexpr float64_min			= limits<float64>::min();

	auto constexpr float32_max			= limits<float32>::max();
	auto constexpr float64_max			= limits<float64>::max();
}

#endif // !_NUMERIC_TYPE_LIMITS_H_
