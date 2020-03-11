#pragma once

#include <cstdint>
#include <cmath>

#include "../../Includes/FrameworkGlobals.h"

#define FORCEINLINE __forceinline

namespace anarchy::framework::math
{
	struct Vec2
	{
	public:
		Vec2()
			:x(0.0f),
			y(0.0f)
		{
		}

		Vec2(float _x, float _y)
			:x(_x),
			y(_y)
		{
		}

		~Vec2()
		{
			x = 0.0f;
			y = 0.0f;
		}

		[[nodiscard]]
		FORCEINLINE float GetLength() const
		{
			return static_cast<float>(sqrt(x * x + y * y));
		}

		[[nodiscard]]
		FORCEINLINE float GetSquaredLength() const
		{
			return (x * x + y * y);
		}

		[[maybe_unused]]
		FORCEINLINE Vec2 Normalize()
		{
			float length = GetLength();
			*this /= length;
			return *this;
		}
		
		// Subscript operator to access elements in the vector
		[[nodiscard]]
		FORCEINLINE float& operator[](const uint8_t index)
		{
			return ((&x)[index]);
		}

		// Subscript operator to access elements in the vector
		[[nodiscard]]
		FORCEINLINE float operator[](const uint8_t index) const
		{
			return ((&x)[index]);
		}

		// Binary Operation for two Vec2
		[[nodiscard]]
		FORCEINLINE Vec2 operator+(const Vec2& operand) const
		{
			Vec2 result;
			result.x = this->x + operand.x;
			result.y = this->y + operand.y;
			
			return result;
		}

		// Binary Operation with a float
		[[nodiscard]]
		FORCEINLINE Vec2 operator+(const float operand) const
		{
			Vec2 result;
			result.x = this->x + operand;
			result.y = this->y + operand;
			
			return result;
		}

		// Unary Operation
		[[nodiscard]]
		FORCEINLINE Vec2 operator+() const
		{
			return *this;
		}

		// Binary Operation for two Vec2
		[[nodiscard]]
		FORCEINLINE Vec2 operator-(const Vec2& operand) const
		{
			Vec2 result;
			result.x = this->x - operand.x;
			result.y = this->y - operand.y;
			
			return result;
		}

		// Binary Operation with a float
		[[nodiscard]]
		FORCEINLINE Vec2 operator-(const float operand) const
		{
			Vec2 result;
			result.x = this->x - operand;
			result.y = this->y - operand;
			
			return result;
		}

		// Unary Operation
		[[nodiscard]]
		FORCEINLINE Vec2 operator-()
		{
			this->x = -this->x;
			this->y = -this->y;
			
			return *this;
		}

		// Binary Operation for two Vec2
		[[nodiscard]]
		FORCEINLINE Vec2 operator*(const Vec2& operand) const
		{
			Vec2 result;
			result.x = this->x * operand.x;
			result.y = this->y * operand.y;

			return result;
		}

		// Binary Operation with a float
		[[nodiscard]]
		FORCEINLINE Vec2 operator*(const float operand) const
		{
			Vec2 result;
			result.x = this->x * operand;
			result.y = this->y * operand;

			return result;
		}

		// Binary Operation for two Vec2
		[[nodiscard]]
		FORCEINLINE Vec2 operator/(const Vec2& operand) const
		{
			//divide by 0 error
			AC_Assert(operand.x != 0.0f || operand.y != 0.0f, "Attempting Divide by 0 | Vector2 Division");

			Vec2 result;
			result.x = this->x / operand.x;
			result.y = this->y / operand.y;
			return result;
		}

		// Binary Operation with a float
		[[nodiscard]]
		FORCEINLINE Vec2 operator/(const float operand) const
		{
			//divide by 0 error
			AC_Assert(operand != 0.0f, "Attempting Divide by 0 | Vector2 Division");

			Vec2 result;
			result.x = this->x / operand;
			result.y = this->y / operand;
			return result;
		}

		[[maybe_unused]]
		FORCEINLINE Vec2 operator+=(const Vec2& operand)
		{
			this->x += operand.x;
			this->y += operand.y;

			return *this;
		}

		[[maybe_unused]]
		FORCEINLINE Vec2 operator+=(const float operand)
		{
			this->x += operand;
			this->y += operand;

			return *this;
		}

		[[maybe_unused]] 
		FORCEINLINE Vec2 operator-=(const Vec2& operand)
		{
			this->x -= operand.x;
			this->y -= operand.y;

			return *this;
		}

		[[maybe_unused]]
		FORCEINLINE Vec2 operator-=(const float operand)
		{
			this->x -= operand;
			this->y -= operand;

			return *this;
		}

		[[maybe_unused]]
		FORCEINLINE Vec2 operator*=(const Vec2& operand)
		{
			this->x *= operand.x;
			this->y *= operand.y;

			return *this;
		}

		[[maybe_unused]] 
		FORCEINLINE Vec2 operator*=(const float operand)
		{
			this->x *= operand;
			this->y *= operand;

			return *this;
		}

		[[maybe_unused]]
		FORCEINLINE Vec2 operator/=(const Vec2& operand)
		{
			//divide by 0 error
			AC_Assert(operand.x != 0.0f || operand.y != 0.0f, "Attempting Divide by 0 | Vector2 Division");

			this->x /= operand.x;
			this->y /= operand.y;

			return *this;
		}

		[[maybe_unused]]
		FORCEINLINE Vec2 operator/=(const float operand)
		{
			//divide by 0 error
			AC_Assert(operand != 0.0f, "Attempting Divide by 0 | Vector2 Division");

			this->x /= operand;
			this->y /= operand;

			return *this;
		}

		[[nodiscard]]
		friend float Dot2(Vec2 vec, Vec2 otherVec)
		{
			return ((vec.x * otherVec.x) + (vec.y * otherVec.y));
		}

		float x;
		float y;
	};
}