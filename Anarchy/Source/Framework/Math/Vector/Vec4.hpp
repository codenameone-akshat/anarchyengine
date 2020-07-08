#pragma once

#include <cmath>
#include <cstdint>

#include "../../Includes/FrameworkGlobals.h"

#define FORCEINLINE __forceinline

namespace anarchy::framework::math
{
	struct Vec4
	{
	public:
		Vec4()
			:x(0.0f),
			y(0.0f),
			z(0.0f),
			w(0.0f)
		{
		}

		Vec4(float _x, float _y, float _z, float _w)
			:x(_x),
			y(_y),
			z(_z),
			w(_w)
		{
		}

		~Vec4()
		{
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
			w = 0.0f;
		}

		[[nodiscard]]
		FORCEINLINE float GetLength() const
		{
			return static_cast<float>(sqrt(x * x + y * y + z * z + w * w));
		}

		[[nodiscard]]
		FORCEINLINE float GetSquaredLength() const
		{
			return (x * x + y * y + z * z + w * w);
		}

		[[maybe_unused]]
		FORCEINLINE Vec4 Normalize()
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

		// Binary Operation for two Vec4
		[[nodiscard]]
		FORCEINLINE Vec4 operator+(const Vec4& operand) const
		{
			Vec4 result;
			result.x = this->x + operand.x;
			result.y = this->y + operand.y;
			result.z = this->z + operand.z;
			result.w = this->w + operand.w;
			return result;
		}

		// Binary Operation with a float
		[[nodiscard]]
		FORCEINLINE Vec4 operator+(const float operand) const
		{
			Vec4 result;
			result.x = this->x + operand;
			result.y = this->y + operand;
			result.z = this->z + operand;
			result.w = this->w + operand;
			return result;
		}

		// Unary Operation
		[[nodiscard]]
		FORCEINLINE Vec4 operator+() const
		{
			return *this;
		}

		// Binary Operation for two Vec4
		[[nodiscard]]
		FORCEINLINE Vec4 operator-(const Vec4& operand) const
		{
			Vec4 result;
			result.x = this->x - operand.x;
			result.y = this->y - operand.y;
			result.z = this->z - operand.z;
			result.w = this->w - operand.w;
			return result;
		}

		// Binary Operation with a float
		[[nodiscard]]
		FORCEINLINE Vec4 operator-(const float operand) const
		{
			Vec4 result;
			result.x = this->x - operand;
			result.y = this->y - operand;
			result.z = this->z - operand;
			result.w = this->w - operand;
			return result;
		}

		// Unary Operation
		[[nodiscard]]
		FORCEINLINE Vec4 operator-()
		{
			this->x = -this->x;
			this->y = -this->y;
			this->z = -this->z;
			this->w = -this->w;
			return *this;
		}

		// Binary Operation for two Vec4
		[[nodiscard]]
		FORCEINLINE Vec4 operator*(const Vec4& operand) const
		{
			Vec4 result;
			result.x = this->x * operand.x;
			result.y = this->y * operand.y;
			result.z = this->z * operand.z;
			result.w = this->w * operand.w;
			return result;
		}

		// Binary Operation with a float
		[[nodiscard]]
		FORCEINLINE Vec4 operator*(const float operand) const
		{
			Vec4 result;
			result.x = this->x * operand;
			result.y = this->y * operand;
			result.z = this->z * operand;
			result.w = this->w * operand;
			return result;
		}

		// Binary Operation for two Vec4
		[[nodiscard]]
		FORCEINLINE Vec4 operator/(const Vec4& operand) const
		{
			//divide by 0 error
			AC_Assert(operand.x != 0.0f || operand.y != 0.0f || operand.z != 0.0f || operand.w != 0.0f, "Attempting Divide by 0 | Vector4 Division");

			Vec4 result;
			result.x = this->x / operand.x;
			result.y = this->y / operand.y;
			result.z = this->z / operand.z;
			result.w = this->w / operand.w;
			return result;
		}

		// Binary Operation with a float
		[[nodiscard]]
		FORCEINLINE Vec4 operator/(const float operand) const
		{
			//divide by 0 error
			AC_Assert(operand != 0.0f, "Attempting Divide by 0 | Vector4 Division");

			Vec4 result;
			result.x = this->x / operand;
			result.y = this->y / operand;
			result.z = this->z / operand;
			result.w = this->w / operand;
			return result;
		}

		[[maybe_unused]]
		FORCEINLINE Vec4 operator+=(const Vec4& operand)
		{
			this->x += operand.x;
			this->y += operand.y;
			this->z += operand.z;
			this->w += operand.w;

			return *this;
		}

		[[maybe_unused]]
		FORCEINLINE Vec4 operator+=(const float operand)
		{
			this->x += operand;
			this->y += operand;
			this->z += operand;
			this->w += operand;

			return *this;
		}

		[[maybe_unused]]
		FORCEINLINE Vec4 operator-=(const Vec4& operand)
		{
			this->x -= operand.x;
			this->y -= operand.y;
			this->z -= operand.z;
			this->w -= operand.w;

			return *this;
		}

		[[maybe_unused]]
		FORCEINLINE Vec4 operator-=(const float operand)
		{
			this->x -= operand;
			this->y -= operand;
			this->z -= operand;
			this->w -= operand;

			return *this;
		}

		[[maybe_unused]]
		FORCEINLINE Vec4 operator*=(const Vec4& operand)
		{
			this->x *= operand.x;
			this->y *= operand.y;
			this->z *= operand.z;
			this->w *= operand.w;

			return *this;
		}

		[[maybe_unused]]
		FORCEINLINE Vec4 operator*=(const float operand)
		{
			this->x *= operand;
			this->y *= operand;
			this->z *= operand;
			this->w *= operand;

			return *this;
		}

		[[maybe_unused]]
		FORCEINLINE Vec4 operator/=(const Vec4& operand)
		{
			//divide by 0 error
			AC_Assert(operand.x != 0.0f || operand.y != 0.0f || operand.z != 0.0f || operand.w != 0.0f, "Attempting Divide by 0 | Vector4 Division");

			this->x /= operand.x;
			this->y /= operand.y;
			this->z /= operand.z;
			this->w /= operand.w;

			return *this;
		}

		[[maybe_unused]]
		FORCEINLINE Vec4 operator/=(const float operand)
		{
			//divide by 0 error
			AC_Assert(operand != 0.0f, "Attempting Divide by 0 | Vector4 Division");

			this->x /= operand;
			this->y /= operand;
			this->z /= operand;
			this->w /= operand;

			return *this;
		}

		[[nodiscard]]
		friend float Dot4(Vec4 vec, Vec4 otherVec)
		{
			return ((vec.x * otherVec.x) + (vec.y * otherVec.y) + (vec.z * otherVec.z) + (vec.w * otherVec.w));
		}

		[[nodiscard]]
		friend Vec4 Cross(Vec4 vec, Vec4 otherVec)
		{
			return (Vec4((vec.y * otherVec.z - vec.z * otherVec.y),
				(vec.z * otherVec.x - vec.x * otherVec.z),
				(vec.x * otherVec.y - vec.y * otherVec.x),
				0.0f));
		}

		// always contiguous
		float x;
		float y;
		float z;
		float w;
	};
}