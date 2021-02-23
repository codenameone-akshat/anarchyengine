#ifndef _VECTOR_3_HPP_
#define _VECTOR_3_HPP_

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
#include <Framework/Math/Vector2.hpp>

// Forward Declaration for Conversion operators
template<class T> struct Vector4;
template<class T> struct Vector2;

namespace anarchy::math
{
    template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    struct Vector3
    {
        enum class Init_Flags
        {
            Init_Zero,
            Init_UnitX,
            Init_UnitY,
            Init_UnitZ
        };

        Vector3(Init_Flags flags = Init_Flags::Init_Zero)
        {
            switch (flags)
            {
            case Init_Flags::Init_Zero: SetZero();
                break;
            case Init_Flags::Init_UnitX: SetUnitX();
                break;
            case Init_Flags::Init_UnitY: SetUnitY();
                break;
            case Init_Flags::Init_UnitZ: SetUnitZ();
                break;
            default: NativeAssert(false, "Undefined Flag");
                break;
            }
        }

        Vector3(T _x, T _y, T _z)
            :x(_x),
            y(_y),
            z(_z)
        {
        }

        ~Vector3()
        {
        }

        SERIALIZE_IMPL()
        {
            SERIALIZE_MEMBER(x);
            SERIALIZE_MEMBER(y);
            SERIALIZE_MEMBER(z);
        }

        [[nodiscard]] 
        FORCEINLINE float GetLength() const
        {
            return static_cast<float>(std::sqrt(x * x + y * y + z * z));
        }

        [[nodiscard]]
        FORCEINLINE float GetSquaredLength() const
        {
            return static_cast<float>(x * x + y * y + z * z);
        }

        [[maybe_unused]] 
        FORCEINLINE Vector3<T> Normalize()
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

        // Binary Operation for two Vec3
        [[nodiscard]]
        FORCEINLINE Vector3<T> operator+(const Vector3<T>& operand) const
        {
            Vector3<T> result;
            result.x = this->x + operand.x;
            result.y = this->y + operand.y;
            result.z = this->z + operand.z;

            return result;
        }

        // Binary Operation with a T
        [[nodiscard]]
        FORCEINLINE Vector3<T> operator+(const T operand) const
        {
            Vector3 result;
            result.x = this->x + operand;
            result.y = this->y + operand;
            result.z = this->z + operand;

            return result;
        }

        // Unary Operation
        [[nodiscard]]
        FORCEINLINE Vector3<T> operator+() const
        {
            return *this;
        }

        // Binary Operation for two Vec3
        [[nodiscard]] 
        FORCEINLINE Vector3<T> operator-(const Vector3<T>& operand) const
        {
            Vector3<T> result;
            result.x = this->x - operand.x;
            result.y = this->y - operand.y;
            result.z = this->z - operand.z;

            return result;
        }

        // Binary Operation with a T
        [[nodiscard]]
        FORCEINLINE Vector3<T> operator-(const T operand) const
        {
            Vector3 result;
            result.x = this->x - operand;
            result.y = this->y - operand;
            result.z = this->z - operand;

            return result;
        }

        // Unary Operation
        [[nodiscard]] 
        FORCEINLINE Vector3<T> operator-()
        {
            this->x = -this->x;
            this->y = -this->y;
            this->z = -this->z;

            return *this;
        }

        // Binary Operation for two Vec3
        [[nodiscard]] 
        FORCEINLINE Vector3<T> operator*(const Vector3<T>& operand) const
        {
            Vector3<T> result;
            result.x = this->x * operand.x;
            result.y = this->y * operand.y;
            result.z = this->z * operand.z;

            return result;
        }

        // Binary Operation with a T
        [[nodiscard]]
        FORCEINLINE Vector3<T> operator*(const T operand) const
        {
            Vector3<T> result;
            result.x = this->x * operand;
            result.y = this->y * operand;
            result.z = this->z * operand;

            return result;
        }

        // Binary Operation for two Vec3
        [[nodiscard]]
        FORCEINLINE Vector3<T> operator/(const Vector3<T>& operand) const
        {
            //divide by 0 error
            NativeAssert(operand.x != 0.0f || operand.y != 0.0f || operand.z != 0.0f, "Attempting Divide by 0 | Vector3 Division");

            Vector3<T> result;
            result.x = this->x / operand.x;
            result.y = this->y / operand.y;
            result.z = this->z / operand.z;

            return result;
        }

        // Binary Operation with a T
        [[nodiscard]]
        FORCEINLINE Vector3<T> operator/(const T operand) const
        {
            //divide by 0 error
            NativeAssert(operand != (T)0, "Attempting Divide by 0 | Vector3 Division");

            Vector3<T> result;
            result.x = this->x / operand;
            result.y = this->y / operand;
            result.z = this->z / operand;

            return result;
        }

        [[maybe_unused]]
        FORCEINLINE Vector3<T> operator+=(const Vector3<T>& operand)
        {
            this->x += operand.x;
            this->y += operand.y;
            this->z += operand.z;

            return *this;
        }

        [[maybe_unused]]
        FORCEINLINE Vector3<T> operator+=(const T operand)
        {
            this->x += operand;
            this->y += operand;
            this->z += operand;

            return *this;
        }

        [[maybe_unused]]
        FORCEINLINE Vector3<T> operator-=(const Vector3<T>& operand)
        {
            this->x -= operand.x;
            this->y -= operand.y;
            this->z -= operand.z;

            return *this;
        }

        [[maybe_unused]]
        FORCEINLINE Vector3<T> operator-=(const T operand)
        {
            this->x -= operand;
            this->y -= operand;
            this->z -= operand;

            return *this;
        }

        [[maybe_unused]] 
        FORCEINLINE Vector3<T> operator*=(const Vector3<T>& operand)
        {
            this->x *= operand.x;
            this->y *= operand.y;
            this->z *= operand.z;

            return *this;
        }

        [[maybe_unused]]
        FORCEINLINE Vector3<T> operator*=(const T operand)
        {
            this->x *= operand;
            this->y *= operand;
            this->z *= operand;

            return *this;
        }

        [[maybe_unused]]
        FORCEINLINE Vector3<T> operator/=(const Vector3<T>& operand)
        {
            //divide by 0 error
            NativeAssert(operand.x != (T)0 || operand.y != (T)0 || operand.z != (T)0, "Attempting Divide by 0 | Vector3 Division");

            this->x /= operand.x;
            this->y /= operand.y;
            this->z /= operand.z;

            return *this;
        }

        [[maybe_unused]]
        FORCEINLINE Vector3<T> operator/=(const T operand)
        {
            //divide by 0 error
            NativeAssert(operand != (T)0, "Attempting Divide by 0 | Vector3 Division");

            this->x /= operand;
            this->y /= operand;
            this->z /= operand;

            return *this;
        }

        [[nodiscard]] 
        FORCEINLINE static float Dot3(Vector3<T> vec, Vector3<T> otherVec)
        {
            return static_cast<float>((vec.x * otherVec.x) + (vec.y * otherVec.y) + (vec.z * otherVec.z));
        }

        [[nodiscard]] 
        FORCEINLINE static Vector3<T> Cross(Vector3<T> vec, Vector3<T> otherVec)
        {
            return (Vector3<T>((vec.y * otherVec.z - vec.z * otherVec.y),
                (vec.z * otherVec.x - vec.x * otherVec.z),
                (vec.x * otherVec.y - vec.y * otherVec.x)));
        }

        [[nodiscard]]
        FORCEINLINE static Vector3<T> Zero()
        {
            return (Vector3<T>((T)0, (T)0, (T)0));
        }

        [[nodiscard]]
        FORCEINLINE static Vector3<T> UnitX()
        {
            return (Vector3<T>(T(1), (T)0, (T)0));
        }

        [[nodiscard]]
        FORCEINLINE static Vector3<T> UnitY()
        {
            return (Vector3<T>((T)0, T(1), (T)0));
        }

        [[nodiscard]]
        FORCEINLINE static Vector3<T> UnitZ()
        {
            return (Vector3<T>((T)0, (T)0, T(1)));
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

        [[nodiscard]]
        FORCEINLINE void SetUnitZ()
        {
            SetZero();
            z = (T)1;
        }

        // Conversion Operators
        operator Vector4<T>() const
        {
            return (Vector4<T>(x, y, z, (T)0));
        }

        operator Vector2<T>() const
        {
            return (Vector2<T>(x, y));
        }

        // Data
        union
        {
            struct
            {
                T x;
                T y;
                T z;
            };
            
            struct
            {
                T r;
                T g;
                T b;
            };

            struct
            {
                T u;
                T v;
                T w;
            };

            T vec[3];
        };
    };
}

#endif // ANARCHY_MATH_ENABLE

#endif // !_VECTOR_3_HPP_