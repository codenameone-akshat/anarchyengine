#ifndef _VECTOR_4_HPP_
#define _VECTOR_4_HPP_

#ifdef ANARCHY_MATH_ENABLE

#ifndef FORCEINLINE
#define FORCEINLINE __forceinline
#endif // !FORCEINLINE

#include <cassert>

#ifndef NativeAssert
#define NativeAssert(cond, message) assert(cond)
#endif // !NativeAssert

#include <Framework/SerializationHelpers.h>
#include <Framework/Math/Vector3.hpp>
#include <Framework/Math/Vector2.hpp>

// Forward Declaration for Conversion operators
template<class T> struct Vector3;
template<class T> struct Vector2;

namespace anarchy::math
{
    template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    struct Vector4
    {
        enum class Init_Flags
        {
            Init_Zero,
            Init_UnitX,
            Init_UnitY,
            Init_UnitZ,
            Init_UnitW
        };

        Vector4(Init_Flags flags = Init_Flags::Init_Zero)
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
            case Init_Flags::Init_UnitW: SetUnitW();
                break;
            default: NativeAssert(false, "Undefined Flag");
                break;
            }
        }

        Vector4(T _x, T _y, T _z, T _w)
            :x(_x),
            y(_y),
            z(_z),
            w(_w)
        {
        }

        ~Vector4()
        {
        }

        SERIALIZE_IMPL()
        {
            SERIALIZE_MEMBER(x);
            SERIALIZE_MEMBER(y);
            SERIALIZE_MEMBER(z);
            SERIALIZE_MEMBER(w);
        }

        [[nodiscard]]
        FORCEINLINE float GetLength() const
        {
            return static_cast<float>(sqrt(x * x + y * y + z * z + w * w));
        }

        [[nodiscard]]
        FORCEINLINE float GetSquaredLength() const
        {
            return static_cast<float>(x * x + y * y + z * z + w * w);
        }

        [[maybe_unused]]
        FORCEINLINE Vector4<T> Normalize()
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

        // Binary Operation for two Vec4
        [[nodiscard]]
        FORCEINLINE Vector4<T> operator+(const Vector4<T>& operand) const
        {
            Vector4<T> result;
            result.x = this->x + operand.x;
            result.y = this->y + operand.y;
            result.z = this->z + operand.z;
            result.w = this->w + operand.w;
            return result;
        }

        // Binary Operation with a T
        [[nodiscard]]
        FORCEINLINE Vector4<T> operator+(const T operand) const
        {
            Vector4<T> result;
            result.x = this->x + operand;
            result.y = this->y + operand;
            result.z = this->z + operand;
            result.w = this->w + operand;
            return result;
        }

        // Unary Operation
        [[nodiscard]]
        FORCEINLINE Vector4 operator+() const
        {
            return *this;
        }

        // Binary Operation for two Vec4
        [[nodiscard]]
        FORCEINLINE Vector4<T> operator-(const Vector4<T>& operand) const
        {
            Vector4<T> result;
            result.x = this->x - operand.x;
            result.y = this->y - operand.y;
            result.z = this->z - operand.z;
            result.w = this->w - operand.w;
            return result;
        }

        // Binary Operation with a T
        [[nodiscard]]
        FORCEINLINE Vector4<T> operator-(const T operand) const
        {
            Vector4<T> result;
            result.x = this->x - operand;
            result.y = this->y - operand;
            result.z = this->z - operand;
            result.w = this->w - operand;
            return result;
        }

        // Unary Operation
        [[nodiscard]]
        FORCEINLINE Vector4<T> operator-()
        {
            this->x = -this->x;
            this->y = -this->y;
            this->z = -this->z;
            this->w = -this->w;
            return *this;
        }

        // Binary Operation for two Vec4
        [[nodiscard]]
        FORCEINLINE Vector4<T> operator*(const Vector4<T>& operand) const
        {
            Vector4<T> result;
            result.x = this->x * operand.x;
            result.y = this->y * operand.y;
            result.z = this->z * operand.z;
            result.w = this->w * operand.w;
            return result;
        }

        // Binary Operation with a T
        [[nodiscard]]
        FORCEINLINE Vector4<T> operator*(const T operand) const
        {
            Vector4 result;
            result.x = this->x * operand;
            result.y = this->y * operand;
            result.z = this->z * operand;
            result.w = this->w * operand;
            return result;
        }

        // Binary Operation for two Vec4
        [[nodiscard]]
        FORCEINLINE Vector4<T> operator/(const Vector4<T>& operand) const
        {
            //divide by 0 error
            NativeAssert(operand.x != (T)0 || operand.y != (T)0 || operand.z != (T)0 || operand.w != (T)0, "Attempting Divide by 0 | Vector4 Division");

            Vector4<T> result;
            result.x = this->x / operand.x;
            result.y = this->y / operand.y;
            result.z = this->z / operand.z;
            result.w = this->w / operand.w;
            return result;
        }

        // Binary Operation with a T
        [[nodiscard]]
        FORCEINLINE Vector4<T> operator/(const T operand) const
        {
            //divide by 0 error
            NativeAssert(operand != (T)0, "Attempting Divide by 0 | Vector4 Division");

            Vector4<T> result;
            result.x = this->x / operand;
            result.y = this->y / operand;
            result.z = this->z / operand;
            result.w = this->w / operand;
            return result;
        }

        [[maybe_unused]]
        FORCEINLINE Vector4<T> operator+=(const Vector4<T>& operand)
        {
            this->x += operand.x;
            this->y += operand.y;
            this->z += operand.z;
            this->w += operand.w;

            return *this;
        }

        [[maybe_unused]]
        FORCEINLINE Vector4<T> operator+=(const T operand)
        {
            this->x += operand;
            this->y += operand;
            this->z += operand;
            this->w += operand;

            return *this;
        }

        [[maybe_unused]]
        FORCEINLINE Vector4<T> operator-=(const Vector4<T>& operand)
        {
            this->x -= operand.x;
            this->y -= operand.y;
            this->z -= operand.z;
            this->w -= operand.w;

            return *this;
        }

        [[maybe_unused]]
        FORCEINLINE Vector4<T> operator-=(const T operand)
        {
            this->x -= operand;
            this->y -= operand;
            this->z -= operand;
            this->w -= operand;

            return *this;
        }

        [[maybe_unused]]
        FORCEINLINE Vector4<T> operator*=(const Vector4<T>& operand)
        {
            this->x *= operand.x;
            this->y *= operand.y;
            this->z *= operand.z;
            this->w *= operand.w;

            return *this;
        }

        [[maybe_unused]]
        FORCEINLINE Vector4<T> operator*=(const T operand)
        {
            this->x *= operand;
            this->y *= operand;
            this->z *= operand;
            this->w *= operand;

            return *this;
        }

        [[maybe_unused]]
        FORCEINLINE Vector4<T> operator/=(const Vector4<T>& operand)
        {
            //divide by 0 error
            NativeAssert(operand.x != (T)0 || operand.y != (T)0 || operand.z != (T)0 || operand.w != (T)0, "Attempting Divide by 0 | Vector4 Division");

            this->x /= operand.x;
            this->y /= operand.y;
            this->z /= operand.z;
            this->w /= operand.w;

            return *this;
        }

        [[maybe_unused]]
        FORCEINLINE Vector4<T> operator/=(const T operand)
        {
            //divide by 0 error
            NativeAssert(operand != (T)0, "Attempting Divide by 0 | Vector4 Division");

            this->x /= operand;
            this->y /= operand;
            this->z /= operand;
            this->w /= operand;

            return *this;
        }

        [[nodiscard]]
        FORCEINLINE static float Dot4(Vector4<T> vec, Vector4<T> otherVec)
        {
            return static_cast<float>((vec.x * otherVec.x) + (vec.y * otherVec.y) + (vec.z * otherVec.z) + (vec.w * otherVec.w));
        }

        [[nodiscard]]
        FORCEINLINE static Vector4<T> Cross(Vector4<T> vec, Vector4<T> otherVec)
        {
            return (Vector4<T>((vec.y * otherVec.z - vec.z * otherVec.y),
                (vec.z * otherVec.x - vec.x * otherVec.z),
                (vec.x * otherVec.y - vec.y * otherVec.x),
                (T)0));
        }

        [[nodiscard]]
        FORCEINLINE static Vector4<T> Zero()
        {
            return (Vector4<T>((T)0, (T)0, (T)0, (T)0));
        }

        [[nodiscard]]
        FORCEINLINE static Vector4<T> UnitX()
        {
            return (Vector4<T>(T(1), (T)0, (T)0, (T)0));
        }

        [[nodiscard]]
        FORCEINLINE static Vector4<T> UnitY()
        {
            return (Vector4<T>((T)0, T(1), (T)0, (T)0));
        }

        [[nodiscard]]
        FORCEINLINE static Vector4<T> UnitZ()
        {
            return (Vector4<T>((T)0, (T)0, T(1), (T)0));
        }

        [[nodiscard]]
        FORCEINLINE static Vector4<T> UnitW()
        {
            return (Vector4<T>((T)0, (T)0, (T)0, T(1)));
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

        [[nodiscard]]
        FORCEINLINE void SetUnitW()
        {
            SetZero();
            w = (T)1;
        }

        // Conversion Operators
        operator Vector3<T>() const
        {
            return (Vector3<T>(x, y, z));
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
                T w;
            };
            
            struct
            {
                T r;
                T g;
                T b;
                T a;
            };

            T vec[4];
        };
    };
}

#endif // ANARCHY_MATH_ENABLE

#endif // !_VECTOR_4_HPP_
