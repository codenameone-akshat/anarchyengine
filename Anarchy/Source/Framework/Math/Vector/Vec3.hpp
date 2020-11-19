#pragma once

#include <cstdint>
#include <cmath>

#include "Framework/Includes/FrameworkGlobals.h"
#include "Framework/Includes/SerializationHelpers.h"

#define FORCEINLINE __forceinline

namespace anarchy::math
{
    template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    struct Vec3
    {
    public:
        Vec3()
            :x(),
            y(),
            z()
        {
        }

        Vec3(float _x, float _y, float _z)
            :x(_x),
            y(_y),
            z(_z)
        {
        }

        ~Vec3()
        {
            x = T();
            y = T();
            z = T();
        }

        SERIALIZE_IMPL()
        {
            SERIALIZE_MEMBER(x);
            SERIALIZE_MEMBER(y);
            SERIALIZE_MEMBER(z);
        }

        [[nodiscard]] FORCEINLINE float GetLength() const
        {
            return static_cast<float>(std::sqrt(x * x + y * y + z * z));
        }

        [[nodiscard]] FORCEINLINE float GetSquaredLength() const
        {
            return (x * x + y * y + z * z);
        }

        [[maybe_unused]] FORCEINLINE Vec3<T> Normalize()
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
        [[nodiscard]] FORCEINLINE Vec3<T> operator+(const Vec3<T>& operand) const
        {
            Vec3<T> result;
            result.x = this->x + operand.x;
            result.y = this->y + operand.y;
            result.z = this->z + operand.z;

            return result;
        }

        // Binary Operation with a T
        [[nodiscard]] FORCEINLINE Vec3<T> operator+(const T operand) const
        {
            Vec3 result;
            result.x = this->x + operand;
            result.y = this->y + operand;
            result.z = this->z + operand;

            return result;
        }

        // Unary Operation
        [[nodiscard]] FORCEINLINE Vec3<T> operator+() const
        {
            return *this;
        }

        // Binary Operation for two Vec3
        [[nodiscard]] FORCEINLINE Vec3<T> operator-(const Vec3<T>& operand) const
        {
            Vec3<T> result;
            result.x = this->x - operand.x;
            result.y = this->y - operand.y;
            result.z = this->z - operand.z;

            return result;
        }

        // Binary Operation with a T
        [[nodiscard]] FORCEINLINE Vec3<T> operator-(const T operand) const
        {
            Vec3 result;
            result.x = this->x - operand;
            result.y = this->y - operand;
            result.z = this->z - operand;

            return result;
        }

        // Unary Operation
        [[nodiscard]] FORCEINLINE Vec3<T> operator-()
        {
            this->x = -this->x;
            this->y = -this->y;
            this->z = -this->z;

            return *this;
        }

        // Binary Operation for two Vec3
        [[nodiscard]] FORCEINLINE Vec3<T> operator*(const Vec3<T>& operand) const
        {
            Vec3<T> result;
            result.x = this->x * operand.x;
            result.y = this->y * operand.y;
            result.z = this->z * operand.z;

            return result;
        }

        // Binary Operation with a T
        [[nodiscard]] FORCEINLINE Vec3<T> operator*(const T operand) const
        {
            Vec3<T> result;
            result.x = this->x * operand;
            result.y = this->y * operand;
            result.z = this->z * operand;

            return result;
        }

        // Binary Operation for two Vec3
        [[nodiscard]] FORCEINLINE Vec3<T> operator/(const Vec3<T>& operand) const
        {
            //divide by 0 error
            AC_Assert(operand.x != 0.0f || operand.y != 0.0f || operand.z != 0.0f, "Attempting Divide by 0 | Vector3 Division");

            Vec3<T> result;
            result.x = this->x / operand.x;
            result.y = this->y / operand.y;
            result.z = this->z / operand.z;

            return result;
        }

        // Binary Operation with a T
        [[nodiscard]] FORCEINLINE Vec3<T> operator/(const T operand) const
        {
            //divide by 0 error
            AC_Assert(operand != 0.0f, "Attempting Divide by 0 | Vector3 Division");

            Vec3<T> result;
            result.x = this->x / operand;
            result.y = this->y / operand;
            result.z = this->z / operand;

            return result;
        }

        [[maybe_unused]] FORCEINLINE Vec3<T> operator+=(const Vec3<T>& operand)
        {
            this->x += operand.x;
            this->y += operand.y;
            this->z += operand.z;

            return *this;
        }

        [[maybe_unused]] FORCEINLINE Vec3<T> operator+=(const T operand)
        {
            this->x += operand;
            this->y += operand;
            this->z += operand;

            return *this;
        }

        [[maybe_unused]] FORCEINLINE Vec3<T> operator-=(const Vec3<T>& operand)
        {
            this->x -= operand.x;
            this->y -= operand.y;
            this->z -= operand.z;

            return *this;
        }

        [[maybe_unused]] FORCEINLINE Vec3<T> operator-=(const T operand)
        {
            this->x -= operand;
            this->y -= operand;
            this->z -= operand;

            return *this;
        }

        [[maybe_unused]] FORCEINLINE Vec3<T> operator*=(const Vec3<T>& operand)
        {
            this->x *= operand.x;
            this->y *= operand.y;
            this->z *= operand.z;

            return *this;
        }

        [[maybe_unused]] FORCEINLINE Vec3<T> operator*=(const T operand)
        {
            this->x *= operand;
            this->y *= operand;
            this->z *= operand;

            return *this;
        }

        [[maybe_unused]] FORCEINLINE Vec3<T> operator/=(const Vec3<T>& operand)
        {
            //divide by 0 error
            AC_Assert(operand.x != 0.0f || operand.y != 0.0f || operand.z != 0.0f, "Attempting Divide by 0 | Vector3 Division");

            this->x /= operand.x;
            this->y /= operand.y;
            this->z /= operand.z;

            return *this;
        }

        [[maybe_unused]] FORCEINLINE Vec3<T> operator/=(const T operand)
        {
            //divide by 0 error
            AC_Assert(operand != 0.0f, "Attempting Divide by 0 | Vector3 Division");

            this->x /= operand;
            this->y /= operand;
            this->z /= operand;

            return *this;
        }

        [[nodiscard]] friend float Dot3(Vec3<T> vec, Vec3<T> otherVec)
        {
            return ((vec.x * otherVec.x) + (vec.y * otherVec.y) + (vec.z * otherVec.z));
        }

        [[nodiscard]] friend Vec3<T> Cross(Vec3<T> vec, Vec3<T> otherVec)
        {
            return (Vec3<T>((vec.y * otherVec.z - vec.z * otherVec.y),
                (vec.z * otherVec.x - vec.x * otherVec.z),
                (vec.x * otherVec.y - vec.y * otherVec.x)));
        }

        float x;
        float y;
        float z;
    };
}