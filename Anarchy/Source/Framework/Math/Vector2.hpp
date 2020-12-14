#ifndef _VECTOR_2_HPP_
#define _VECTOR_2_HPP_

#ifdef ANARCHY_MATH_ENABLE

#ifndef FORCEINLINE
#define FORCEINLINE __forceinline
#endif // !FORCEINLINE

#include <cassert>

#ifndef NativeAssert
#define NativeAssert(cond, message) assert(cond)
#endif // NativeAssert

#include <Framework/SerializationHelpers.h>
#include <Framework/Math/Vector4.hpp>
#include <Framework/Math/Vector3.hpp>

// Forward Declaration for Conversion operators
template<class T> struct Vector4;
template<class T> struct Vector3;

namespace anarchy::math
{
	template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
	struct Vector2
	{
		enum class Init_Flags
		{
			Init_Zero,
			Init_UnitX,
			Init_UnitY
		};

		Vector2(Init_Flags flags = Init_Flags::Init_Zero)
		{
			switch (flags)
			{
			case Init_Flags::Init_Zero: SetZero();
				break;
			case Init_Flags::Init_UnitX: SetUnitX();
				break;
			case Init_Flags::Init_UnitY: SetUnitY();
				break;
			default: NativeAssert(false, "Undefined Flag");
				break;
			}
		}

		Vector2(T _x, T _y)
			:x(_x),
			y(_y)
		{
		}

		~Vector2()
		{
			x = T();
			y = T();
		}

		SERIALIZE_IMPL()
		{
			SERIALIZE_MEMBER(x);
			SERIALIZE_MEMBER(y);
		}

		[[nodiscard]]
		FORCEINLINE float GetLength() const
		{
			return static_cast<float>(sqrt(x * x + y * y));
		}

		[[nodiscard]]
		FORCEINLINE float GetSquaredLength() const
		{
			return static_cast<float>(x * x + y * y);
		}

		[[maybe_unused]]
		FORCEINLINE Vector2<T> Normalize()
		{
			float length = GetLength();
			*this /= length;
			return *this;
		}

		// Subscript operator to access elements in the vector
		[[nodiscard]]
		FORCEINLINE T& operator[](const uint8_t index)
		{
			return ((&x)[index]);
		}

		// Subscript operator to access elements in the vector
		[[nodiscard]]
		FORCEINLINE T operator[](const uint8_t index) const
		{
			return ((&x)[index]);
		}

		// Binary Operation for two Vec2<T>
		[[nodiscard]]
		FORCEINLINE Vector2<T> operator+(const Vector2<T>& operand) const
		{
			Vector2<T> result;
			result.x = this->x + operand.x;
			result.y = this->y + operand.y;

			return result;
		}

		// Binary Operation with a T
		[[nodiscard]]
		FORCEINLINE Vector2<T> operator+(const T operand) const
		{
			Vector2<T> result;
			result.x = this->x + operand;
			result.y = this->y + operand;

			return result;
		}

		// Unary Operation
		[[nodiscard]]
		FORCEINLINE Vector2<T> operator+() const
		{
			return *this;
		}

		// Binary Operation for two Vec2<T>
		[[nodiscard]]
		FORCEINLINE Vector2<T> operator-(const Vector2<T>& operand) const
		{
			Vector2<T> result;
			result.x = this->x - operand.x;
			result.y = this->y - operand.y;

			return result;
		}

		// Binary Operation with a T
		[[nodiscard]]
		FORCEINLINE Vector2<T> operator-(const T operand) const
		{
			Vector2<T> result;
			result.x = this->x - operand;
			result.y = this->y - operand;

			return result;
		}

		// Unary Operation
		[[nodiscard]]
		FORCEINLINE Vector2<T> operator-()
		{
			this->x = -this->x;
			this->y = -this->y;

			return *this;
		}

		// Binary Operation for two Vec2<T>
		[[nodiscard]]
		FORCEINLINE Vector2<T> operator*(const Vector2<T>& operand) const
		{
			Vector2<T> result;
			result.x = this->x * operand.x;
			result.y = this->y * operand.y;

			return result;
		}

		// Binary Operation with a T
		[[nodiscard]]
		FORCEINLINE Vector2<T> operator*(const T operand) const
		{
			Vector2<T> result;
			result.x = this->x * operand;
			result.y = this->y * operand;

			return result;
		}

		// Binary Operation for two Vec2<T>
		[[nodiscard]]
		FORCEINLINE Vector2<T> operator/(const Vector2<T>& operand) const
		{
			//divide by 0 error
			NativeAssert(operand.x != (T)0 || operand.y != (T)0, "Attempting Divide by 0 | Vector2 Division");

			Vector2<T> result;
			result.x = this->x / operand.x;
			result.y = this->y / operand.y;
			return result;
		}

		// Binary Operation with a T
		[[nodiscard]]
		FORCEINLINE Vector2<T> operator/(const T operand) const
		{
			//divide by 0 error
			NativeAssert(operand != (T)0, "Attempting Divide by 0 | Vector2 Division");

			Vector2<T> result;
			result.x = this->x / operand;
			result.y = this->y / operand;
			return result;
		}

		[[maybe_unused]]
		FORCEINLINE Vector2<T> operator+=(const Vector2<T>& operand)
		{
			this->x += operand.x;
			this->y += operand.y;

			return *this;
		}

		[[maybe_unused]]
		FORCEINLINE Vector2<T> operator+=(const T operand)
		{
			this->x += operand;
			this->y += operand;

			return *this;
		}

		[[maybe_unused]]
		FORCEINLINE Vector2<T> operator-=(const Vector2<T>& operand)
		{
			this->x -= operand.x;
			this->y -= operand.y;

			return *this;
		}

		[[maybe_unused]]
		FORCEINLINE Vector2<T> operator-=(const T operand)
		{
			this->x -= operand;
			this->y -= operand;

			return *this;
		}

		[[maybe_unused]]
		FORCEINLINE Vector2<T> operator*=(const Vector2<T>& operand)
		{
			this->x *= operand.x;
			this->y *= operand.y;

			return *this;
		}

		[[maybe_unused]]
		FORCEINLINE Vector2<T> operator*=(const T operand)
		{
			this->x *= operand;
			this->y *= operand;

			return *this;
		}

		[[maybe_unused]]
		FORCEINLINE Vector2<T> operator/=(const Vector2<T>& operand)
		{
			//divide by 0 error
			NativeAssert(operand.x != (T)0 || operand.y != (T)0, "Attempting Divide by 0 | Vector2 Division");

			this->x /= operand.x;
			this->y /= operand.y;

			return *this;
		}

		[[maybe_unused]]
		FORCEINLINE Vector2<T> operator/=(const T operand)
		{
			//divide by 0 error
			NativeAssert(operand != (T)0, "Attempting Divide by 0 | Vector2 Division");

			this->x /= operand;
			this->y /= operand;

			return *this;
		}

		[[nodiscard]]
		FORCEINLINE static float Dot2(Vector2<T> vec, Vector2<T> otherVec)
		{
			return static_cast<float>((vec.x * otherVec.x) + (vec.y * otherVec.y));
		}

		[[nodiscard]]
		FORCEINLINE static Vector2<T> Zero()
		{
			return (Vector2<T>((T)0, (T)0));
		}

		[[nodiscard]]
		FORCEINLINE static Vector2<T> UnitX()
		{
			return (Vector2<T>((T)1, (T)0));
		}

		[[nodiscard]]
		FORCEINLINE static Vector2<T> UnitY()
		{
			return (Vector2<T>((T)0, (T)1));
		}

		[[nodiscard]]
		FORCEINLINE void SetZero()
		{
			std::memset(vec, 0, sizeof(vec));
		}

		[[nodiscard]]
		FORCEINLINE void SetUnitX()
		{
			SetZero();
			x = (T)1;
		}

		[[nodiscard]]
		FORCEINLINE void SetUnitY()
		{
			SetZero();
			y = (T)1;
		}

		// Conversion Operators
		operator Vector4<T>() const
		{
			return (Vector4<T>(x, y, (T)0, (T)0));
		}

		operator Vector3<T>() const
		{
			return (Vector3<T>(x, y, (T)0));
		}

		// Data
		union
		{
			struct
			{
				T x;
				T y;
			};
			
			struct
			{
				T r;
				T g;
			};
			
			struct 
			{
				T u;
				T v;
			};

			T vec[2];
		};
	};
}

#endif // ANARCHY_MATH_ENABLE

#endif // !_VECTOR_2_HPP_
