#pragma once

#include <cstdint>
#include <cmath>

#include "../../Includes/FrameworkGlobals.h"
#include "../../Includes/SerializationHelpers.h"

#define FORCEINLINE __forceinline

namespace anarchy::math
{
    template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    struct Vec2
    {
    public:
        Vec2()
            :x(),
            y()
        {
        }

        Vec2(T _x, T _y)
            :x(_x),
            y(_y)
        {
        }

        ~Vec2()
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
        FORCEINLINE Vec2<T> Normalize()
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
        FORCEINLINE Vec2<T> operator+(const Vec2<T>& operand) const
        {
            Vec2<T> result;
            result.x = this->x + operand.x;
            result.y = this->y + operand.y;

            return result;
        }

        // Binary Operation with a T
        [[nodiscard]]
        FORCEINLINE Vec2<T> operator+(const T operand) const
        {
            Vec2<T> result;
            result.x = this->x + operand;
            result.y = this->y + operand;

            return result;
        }

        // Unary Operation
        [[nodiscard]]
        FORCEINLINE Vec2<T> operator+() const
        {
            return *this;
        }

        // Binary Operation for two Vec2<T>
        [[nodiscard]]
        FORCEINLINE Vec2<T> operator-(const Vec2<T>& operand) const
        {
            Vec2<T> result;
            result.x = this->x - operand.x;
            result.y = this->y - operand.y;

            return result;
        }

        // Binary Operation with a T
        [[nodiscard]]
        FORCEINLINE Vec2<T> operator-(const T operand) const
        {
            Vec2<T> result;
            result.x = this->x - operand;
            result.y = this->y - operand;

            return result;
        }

        // Unary Operation
        [[nodiscard]]
        FORCEINLINE Vec2<T> operator-()
        {
            this->x = -this->x;
            this->y = -this->y;

            return *this;
        }

        // Binary Operation for two Vec2<T>
        [[nodiscard]]
        FORCEINLINE Vec2<T> operator*(const Vec2<T>& operand) const
        {
            Vec2<T> result;
            result.x = this->x * operand.x;
            result.y = this->y * operand.y;

            return result;
        }

        // Binary Operation with a T
        [[nodiscard]]
        FORCEINLINE Vec2<T> operator*(const T operand) const
        {
            Vec2<T> result;
            result.x = this->x * operand;
            result.y = this->y * operand;

            return result;
        }

        // Binary Operation for two Vec2<T>
        [[nodiscard]]
        FORCEINLINE Vec2<T> operator/(const Vec2<T>& operand) const
        {
            //divide by 0 error
            AC_Assert(operand.x != 0.0f || operand.y != 0.0f, "Attempting Divide by 0 | Vector2 Division");

            Vec2<T> result;
            result.x = this->x / operand.x;
            result.y = this->y / operand.y;
            return result;
        }

        // Binary Operation with a T
        [[nodiscard]]
        FORCEINLINE Vec2<T> operator/(const T operand) const
        {
            //divide by 0 error
            AC_Assert(operand != 0.0f, "Attempting Divide by 0 | Vector2 Division");

            Vec2<T> result;
            result.x = this->x / operand;
            result.y = this->y / operand;
            return result;
        }

        [[maybe_unused]]
        FORCEINLINE Vec2<T> operator+=(const Vec2<T>& operand)
        {
            this->x += operand.x;
            this->y += operand.y;

            return *this;
        }

        [[maybe_unused]]
        FORCEINLINE Vec2<T> operator+=(const T operand)
        {
            this->x += operand;
            this->y += operand;

            return *this;
        }

        [[maybe_unused]]
        FORCEINLINE Vec2<T> operator-=(const Vec2<T>& operand)
        {
            this->x -= operand.x;
            this->y -= operand.y;

            return *this;
        }

        [[maybe_unused]]
        FORCEINLINE Vec2<T> operator-=(const T operand)
        {
            this->x -= operand;
            this->y -= operand;

            return *this;
        }

        [[maybe_unused]]
        FORCEINLINE Vec2<T> operator*=(const Vec2<T>& operand)
        {
            this->x *= operand.x;
            this->y *= operand.y;

            return *this;
        }

        [[maybe_unused]]
        FORCEINLINE Vec2<T> operator*=(const T operand)
        {
            this->x *= operand;
            this->y *= operand;

            return *this;
        }

        [[maybe_unused]]
        FORCEINLINE Vec2<T> operator/=(const Vec2<T>& operand)
        {
            //divide by 0 error
            AC_Assert(operand.x != 0.0f || operand.y != 0.0f, "Attempting Divide by 0 | Vector2 Division");

            this->x /= operand.x;
            this->y /= operand.y;

            return *this;
        }

        [[maybe_unused]]
        FORCEINLINE Vec2<T> operator/=(const T operand)
        {
            //divide by 0 error
            AC_Assert(operand != 0.0f, "Attempting Divide by 0 | Vector2 Division");

            this->x /= operand;
            this->y /= operand;

            return *this;
        }

        [[nodiscard]]
        friend float Dot2(Vec2<T> vec, Vec2<T> otherVec)
        {
            return static_cast<float>((vec.x * otherVec.x) + (vec.y * otherVec.y));
        }

        T x;
        T y;
    };
}