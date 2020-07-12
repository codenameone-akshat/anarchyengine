#pragma once

#include <cmath>
#include <cstdint>

#include "../../Includes/FrameworkGlobals.h"
#include "../../Includes/SerializationHelpers.h"

#define FORCEINLINE __forceinline

namespace anarchy::math
{
    template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    struct Vec4
    {
    public:
        Vec4()
            :x(),
            y(),
            z(),
            w()
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
            x = T();
            y = T();
            z = T();
            w = T();
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
            return (x * x + y * y + z * z + w * w);
        }

        [[maybe_unused]]
        FORCEINLINE Vec4<T> Normalize()
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
        FORCEINLINE Vec4<T> operator+(const Vec4<T>& operand) const
        {
            Vec4<T> result;
            result.x = this->x + operand.x;
            result.y = this->y + operand.y;
            result.z = this->z + operand.z;
            result.w = this->w + operand.w;
            return result;
        }

        // Binary Operation with a T
        [[nodiscard]]
        FORCEINLINE Vec4<T> operator+(const T operand) const
        {
            Vec4<T> result;
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
        FORCEINLINE Vec4<T> operator-(const Vec4<T>& operand) const
        {
            Vec4<T> result;
            result.x = this->x - operand.x;
            result.y = this->y - operand.y;
            result.z = this->z - operand.z;
            result.w = this->w - operand.w;
            return result;
        }

        // Binary Operation with a T
        [[nodiscard]]
        FORCEINLINE Vec4<T> operator-(const T operand) const
        {
            Vec4<T> result;
            result.x = this->x - operand;
            result.y = this->y - operand;
            result.z = this->z - operand;
            result.w = this->w - operand;
            return result;
        }

        // Unary Operation
        [[nodiscard]]
        FORCEINLINE Vec4<T> operator-()
        {
            this->x = -this->x;
            this->y = -this->y;
            this->z = -this->z;
            this->w = -this->w;
            return *this;
        }

        // Binary Operation for two Vec4
        [[nodiscard]]
        FORCEINLINE Vec4<T> operator*(const Vec4<T>& operand) const
        {
            Vec4<T> result;
            result.x = this->x * operand.x;
            result.y = this->y * operand.y;
            result.z = this->z * operand.z;
            result.w = this->w * operand.w;
            return result;
        }

        // Binary Operation with a T
        [[nodiscard]]
        FORCEINLINE Vec4<T> operator*(const T operand) const
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
        FORCEINLINE Vec4<T> operator/(const Vec4<T>& operand) const
        {
            //divide by 0 error
            AC_Assert(operand.x != 0.0f || operand.y != 0.0f || operand.z != 0.0f || operand.w != 0.0f, "Attempting Divide by 0 | Vector4 Division");

            Vec4<T> result;
            result.x = this->x / operand.x;
            result.y = this->y / operand.y;
            result.z = this->z / operand.z;
            result.w = this->w / operand.w;
            return result;
        }

        // Binary Operation with a T
        [[nodiscard]]
        FORCEINLINE Vec4<T> operator/(const T operand) const
        {
            //divide by 0 error
            AC_Assert(operand != 0.0f, "Attempting Divide by 0 | Vector4 Division");

            Vec4<T> result;
            result.x = this->x / operand;
            result.y = this->y / operand;
            result.z = this->z / operand;
            result.w = this->w / operand;
            return result;
        }

        [[maybe_unused]]
        FORCEINLINE Vec4<T> operator+=(const Vec4<T>& operand)
        {
            this->x += operand.x;
            this->y += operand.y;
            this->z += operand.z;
            this->w += operand.w;

            return *this;
        }

        [[maybe_unused]]
        FORCEINLINE Vec4<T> operator+=(const T operand)
        {
            this->x += operand;
            this->y += operand;
            this->z += operand;
            this->w += operand;

            return *this;
        }

        [[maybe_unused]]
        FORCEINLINE Vec4<T> operator-=(const Vec4<T>& operand)
        {
            this->x -= operand.x;
            this->y -= operand.y;
            this->z -= operand.z;
            this->w -= operand.w;

            return *this;
        }

        [[maybe_unused]]
        FORCEINLINE Vec4<T> operator-=(const T operand)
        {
            this->x -= operand;
            this->y -= operand;
            this->z -= operand;
            this->w -= operand;

            return *this;
        }

        [[maybe_unused]]
        FORCEINLINE Vec4<T> operator*=(const Vec4<T>& operand)
        {
            this->x *= operand.x;
            this->y *= operand.y;
            this->z *= operand.z;
            this->w *= operand.w;

            return *this;
        }

        [[maybe_unused]]
        FORCEINLINE Vec4<T> operator*=(const T operand)
        {
            this->x *= operand;
            this->y *= operand;
            this->z *= operand;
            this->w *= operand;

            return *this;
        }

        [[maybe_unused]]
        FORCEINLINE Vec4<T> operator/=(const Vec4<T>& operand)
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
        FORCEINLINE Vec4<T> operator/=(const T operand)
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
        friend float Dot4(Vec4<T> vec, Vec4<T> otherVec)
        {
            return ((vec.x * otherVec.x) + (vec.y * otherVec.y) + (vec.z * otherVec.z) + (vec.w * otherVec.w));
        }

        [[nodiscard]]
        friend Vec4 Cross(Vec4<T> vec, Vec4<T> otherVec)
        {
            return (Vec4<T>((vec.y * otherVec.z - vec.z * otherVec.y),
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