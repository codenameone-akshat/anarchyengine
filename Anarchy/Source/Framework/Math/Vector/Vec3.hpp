#pragma once

#include <cstdint>
#include <cmath>

#include "../../Includes/FrameworkGlobals.h"
#include "../../Includes/SerializationHelpers.h"

#define FORCEINLINE __forceinline

namespace anarchy::math
{
    struct Vec3
    {
    public:
        Vec3()
            :x(0.0f),
            y(0.0f),
            z(0.0f)
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
            x = 0.0f;
            y = 0.0f;
            z = 0.0f;
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

        [[maybe_unused]] FORCEINLINE Vec3 Normalize()
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

        // Binary Operation for two Vec3
        [[nodiscard]] FORCEINLINE Vec3 operator+(const Vec3& operand) const
        {
            Vec3 result;
            result.x = this->x + operand.x;
            result.y = this->y + operand.y;
            result.z = this->z + operand.z;

            return result;
        }

        // Binary Operation with a float
        [[nodiscard]] FORCEINLINE Vec3 operator+(const float operand) const
        {
            Vec3 result;
            result.x = this->x + operand;
            result.y = this->y + operand;
            result.z = this->z + operand;

            return result;
        }

        // Unary Operation
        [[nodiscard]] FORCEINLINE Vec3 operator+() const
        {
            return *this;
        }

        // Binary Operation for two Vec3
        [[nodiscard]] FORCEINLINE Vec3 operator-(const Vec3& operand) const
        {
            Vec3 result;
            result.x = this->x - operand.x;
            result.y = this->y - operand.y;
            result.z = this->z - operand.z;

            return result;
        }

        // Binary Operation with a float
        [[nodiscard]] FORCEINLINE Vec3 operator-(const float operand) const
        {
            Vec3 result;
            result.x = this->x - operand;
            result.y = this->y - operand;
            result.z = this->z - operand;

            return result;
        }

        // Unary Operation
        [[nodiscard]] FORCEINLINE Vec3 operator-()
        {
            this->x = -this->x;
            this->y = -this->y;
            this->z = -this->z;

            return *this;
        }

        // Binary Operation for two Vec3
        [[nodiscard]] FORCEINLINE Vec3 operator*(const Vec3& operand) const
        {
            Vec3 result;
            result.x = this->x * operand.x;
            result.y = this->y * operand.y;
            result.z = this->z * operand.z;

            return result;
        }

        // Binary Operation with a float
        [[nodiscard]] FORCEINLINE Vec3 operator*(const float operand) const
        {
            Vec3 result;
            result.x = this->x * operand;
            result.y = this->y * operand;
            result.z = this->z * operand;

            return result;
        }

        // Binary Operation for two Vec3
        [[nodiscard]] FORCEINLINE Vec3 operator/(const Vec3& operand) const
        {
            //divide by 0 error
            AC_Assert(operand.x != 0.0f || operand.y != 0.0f || operand.z != 0.0f, "Attempting Divide by 0 | Vector3 Division");

            Vec3 result;
            result.x = this->x / operand.x;
            result.y = this->y / operand.y;
            result.z = this->z / operand.z;

            return result;
        }

        // Binary Operation with a float
        [[nodiscard]] FORCEINLINE Vec3 operator/(const float operand) const
        {
            //divide by 0 error
            AC_Assert(operand != 0.0f, "Attempting Divide by 0 | Vector3 Division");

            Vec3 result;
            result.x = this->x / operand;
            result.y = this->y / operand;
            result.z = this->z / operand;

            return result;
        }

        [[maybe_unused]] FORCEINLINE Vec3 operator+=(const Vec3& operand)
        {
            this->x += operand.x;
            this->y += operand.y;
            this->z += operand.z;

            return *this;
        }

        [[maybe_unused]] FORCEINLINE Vec3 operator+=(const float operand)
        {
            this->x += operand;
            this->y += operand;
            this->z += operand;

            return *this;
        }

        [[maybe_unused]] FORCEINLINE Vec3 operator-=(const Vec3& operand)
        {
            this->x -= operand.x;
            this->y -= operand.y;
            this->z -= operand.z;

            return *this;
        }

        [[maybe_unused]] FORCEINLINE Vec3 operator-=(const float operand)
        {
            this->x -= operand;
            this->y -= operand;
            this->z -= operand;

            return *this;
        }

        [[maybe_unused]] FORCEINLINE Vec3 operator*=(const Vec3& operand)
        {
            this->x *= operand.x;
            this->y *= operand.y;
            this->z *= operand.z;

            return *this;
        }

        [[maybe_unused]] FORCEINLINE Vec3 operator*=(const float operand)
        {
            this->x *= operand;
            this->y *= operand;
            this->z *= operand;

            return *this;
        }

        [[maybe_unused]] FORCEINLINE Vec3 operator/=(const Vec3& operand)
        {
            //divide by 0 error
            AC_Assert(operand.x != 0.0f || operand.y != 0.0f || operand.z != 0.0f, "Attempting Divide by 0 | Vector3 Division");

            this->x /= operand.x;
            this->y /= operand.y;
            this->z /= operand.z;

            return *this;
        }

        [[maybe_unused]] FORCEINLINE Vec3 operator/=(const float operand)
        {
            //divide by 0 error
            AC_Assert(operand != 0.0f, "Attempting Divide by 0 | Vector3 Division");

            this->x /= operand;
            this->y /= operand;
            this->z /= operand;

            return *this;
        }

        [[nodiscard]] friend float Dot3(Vec3 vec, Vec3 otherVec)
        {
            return ((vec.x * otherVec.x) + (vec.y * otherVec.y) + (vec.z * otherVec.z));
        }

        [[nodiscard]] friend Vec3 Cross(Vec3 vec, Vec3 otherVec)
        {
            return (Vec3((vec.y * otherVec.z - vec.z * otherVec.y),
                (vec.z * otherVec.x - vec.x * otherVec.z),
                (vec.x * otherVec.y - vec.y * otherVec.x)));
        }

        float x;
        float y;
        float z;
    };
}