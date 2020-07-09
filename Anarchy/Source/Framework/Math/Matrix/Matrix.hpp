#pragma once

#include <cstring>

#include "../Vector/Vec4.hpp"
#include "../Vector/Vec3.hpp"
#include "../Vector/Vec2.hpp"
#include "../../Includes/FrameworkGlobals.h"

#define FORCEINLINE __forceinline

namespace anarchy::math
{
    class Matrix4
    {
    public:
        Matrix4()
        {
            std::memset(m, 0, sizeof(m));
        }

        ~Matrix4()
        {
        }

        FORCEINLINE void MakeIdentity()
        {
            std::memset(m, 0, sizeof(m));
            m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1;
        }

        FORCEINLINE void ZeroMatrix()
        {
            std::memset(m, 0, sizeof(m));
        }

        FORCEINLINE void Transpose()
        {
            Matrix4 result;
            for (uint32_t rItr = 0; rItr < 4; ++rItr)
            {
                for (uint32_t cItr = 0; cItr < 4; ++cItr)
                {
                    result.m[rItr][cItr] = m[cItr][rItr];
                }
            }

            *this = result;
        }

        [[nodiscard]]
        FORCEINLINE Vec4 GetRowVecAtIndex(uint32_t idx) const
        {
            AC_Assert(idx < 4, "Vector4 Requested Index > 4");

            Vec4 row;
            memcpy(&row, &m[idx][0], sizeof(Vec4));
            return row;
        }

        [[nodiscard]]
        FORCEINLINE static Matrix4 GetTransposed(Matrix4 otherMat)
        {
            otherMat.Transpose();
            return otherMat;
        }

        [[nodiscard]]
        FORCEINLINE static Matrix4 GetIdentity()
        {
            Matrix4 mIdentity;
            mIdentity.MakeIdentity();
            return mIdentity;
        }

        [[nodiscard]]
        FORCEINLINE static Matrix4 GetZero()
        {
            Matrix4 mZero;
            return mZero;
        }

        [[nodiscard]]
        FORCEINLINE float Trace()
        {
            // Sum of the main diagonal
            return (m[0][0] + m[1][1] + m[2][2] + m[3][3]);
        }

        FORCEINLINE float Determinant()
        {
            // Column wise to support implicit SIMD
            return (
                m[0][0] * (
                    m[1][1] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) -
                    m[2][1] * (m[1][2] * m[3][3] - m[1][3] * m[3][2]) +
                    m[3][1] * (m[1][2] * m[2][3] - m[1][3] * m[2][2])
                    ) -
                m[1][0] * (
                    m[0][1] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) -
                    m[2][1] * (m[0][2] * m[3][3] - m[0][3] * m[3][2]) +
                    m[3][1] * (m[0][2] * m[2][3] - m[0][3] * m[2][2])
                    ) +
                m[2][0] * (
                    m[0][1] * (m[1][2] * m[3][3] - m[1][3] * m[3][2]) -
                    m[1][1] * (m[0][2] * m[3][3] - m[0][3] * m[3][2]) +
                    m[3][1] * (m[0][2] * m[1][3] - m[0][3] * m[1][2])
                    ) -
                m[3][0] * (
                    m[0][1] * (m[1][2] * m[2][3] - m[1][3] * m[2][2]) -
                    m[1][1] * (m[0][2] * m[2][3] - m[0][3] * m[2][2]) +
                    m[2][1] * (m[0][2] * m[1][3] - m[0][3] * m[1][2])
                    )
                );
        }

        FORCEINLINE float Determinant3()
        {
            // Column wise to support implicit SIMD

            return (m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) -
                m[1][0] * (m[0][1] * m[2][2] - m[0][2] * m[2][1]) +
                m[2][0] * (m[0][1] * m[1][2] - m[0][2] * m[1][1]));
        }

        FORCEINLINE Matrix4 Adjoint()
        {
            Matrix4 adjoint;
            adjoint.MakeIdentity();

            // col 1
            adjoint.m[0][0] =
                m[1][1] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) -
                m[2][1] * (m[1][2] * m[3][3] - m[1][3] * m[3][2]) +
                m[3][1] * (m[1][2] * m[2][3] - m[1][3] * m[2][2]);

            adjoint.m[1][0] = -(
                m[0][1] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) -
                m[2][1] * (m[0][2] * m[3][3] - m[0][3] * m[3][2]) +
                m[3][1] * (m[0][2] * m[2][3] - m[0][3] * m[2][2]));

            adjoint.m[2][0] =
                m[0][1] * (m[1][2] * m[3][3] - m[1][3] * m[3][2]) -
                m[1][1] * (m[0][2] * m[3][3] - m[0][3] * m[3][2]) +
                m[3][1] * (m[0][2] * m[1][3] - m[0][3] * m[1][2]);

            adjoint.m[3][0] = -(
                m[0][1] * (m[1][2] * m[2][3] - m[1][3] * m[2][2]) -
                m[1][1] * (m[0][2] * m[2][3] - m[0][3] * m[2][2]) +
                m[2][1] * (m[0][2] * m[1][3] - m[0][3] * m[1][2]));

            // col 2
            adjoint.m[0][1] = -(
                m[1][0] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) -
                m[2][0] * (m[1][2] * m[3][3] - m[1][3] * m[3][2]) +
                m[3][0] * (m[1][2] * m[2][3] - m[1][3] * m[2][2]));

            adjoint.m[1][1] =
                m[0][0] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) -
                m[2][0] * (m[0][2] * m[3][3] - m[0][3] * m[3][2]) +
                m[3][0] * (m[0][2] * m[2][3] - m[0][3] * m[2][2]);

            adjoint.m[2][1] = -(
                m[0][0] * (m[1][2] * m[3][3] - m[1][3] * m[3][2]) -
                m[1][0] * (m[0][2] * m[3][3] - m[0][3] * m[3][2]) +
                m[3][0] * (m[0][2] * m[1][3] - m[0][3] * m[1][2]));

            adjoint.m[3][1] =
                m[0][0] * (m[1][2] * m[2][3] - m[1][3] * m[2][2]) -
                m[1][0] * (m[0][2] * m[2][3] - m[0][3] * m[2][2]) +
                m[2][0] * (m[0][2] * m[1][3] - m[0][3] * m[1][2]);

            // col 3
            adjoint.m[0][2] =
                m[1][0] * (m[2][1] * m[3][3] - m[2][3] * m[3][1]) -
                m[2][0] * (m[1][1] * m[3][3] - m[1][3] * m[3][1]) +
                m[3][0] * (m[1][1] * m[2][3] - m[1][3] * m[2][1]);

            adjoint.m[1][2] = -(
                m[0][0] * (m[2][1] * m[3][3] - m[2][3] * m[3][1]) -
                m[2][0] * (m[0][1] * m[3][3] - m[0][3] * m[3][1]) +
                m[3][0] * (m[0][1] * m[2][3] - m[0][3] * m[2][1]));

            adjoint.m[2][2] =
                m[0][0] * (m[1][1] * m[3][3] - m[1][3] * m[3][1]) -
                m[1][0] * (m[0][1] * m[3][3] - m[0][3] * m[3][1]) +
                m[3][0] * (m[0][1] * m[1][3] - m[0][3] * m[1][1]);

            adjoint.m[3][2] = -(
                m[0][0] * (m[1][1] * m[2][3] - m[1][3] * m[2][1]) -
                m[1][0] * (m[0][1] * m[2][3] - m[0][3] * m[2][1]) +
                m[2][0] * (m[0][1] * m[1][3] - m[0][3] * m[1][1]));

            // col 4
            adjoint.m[0][3] = -(
                m[1][0] * (m[2][1] * m[3][2] - m[2][2] * m[3][1]) -
                m[2][0] * (m[1][1] * m[3][2] - m[1][2] * m[3][1]) +
                m[3][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]));

            adjoint.m[1][3] =
                m[0][0] * (m[2][1] * m[3][2] - m[2][2] * m[3][1]) -
                m[2][0] * (m[0][1] * m[3][2] - m[0][2] * m[3][1]) +
                m[3][0] * (m[0][1] * m[2][2] - m[0][2] * m[2][1]);

            adjoint.m[2][3] = -(
                m[0][0] * (m[1][1] * m[3][2] - m[1][2] * m[3][1]) -
                m[1][0] * (m[0][1] * m[3][2] - m[0][2] * m[3][1]) +
                m[3][0] * (m[0][1] * m[1][2] - m[0][2] * m[1][1]));

            adjoint.m[3][3] =
                m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) -
                m[1][0] * (m[0][1] * m[2][2] - m[0][2] * m[2][1]) +
                m[2][0] * (m[0][1] * m[1][2] - m[0][2] * m[1][1]);

            return adjoint;
        }

        FORCEINLINE void MatrixTranslate(const float x, const float y, const float z)
        {
            m[3][0] += x;
            m[3][1] += y;
            m[3][2] += z;
        }

        FORCEINLINE void MatrixScaleUniform(const float scale)
        {
            m[0][0] *= scale;
            m[1][1] *= scale;
            m[2][2] *= scale;
        }

        FORCEINLINE void MatrixScale(const float xScale, const float yScale, const float zScale)
        {
            m[0][0] *= xScale;
            m[1][1] *= yScale;
            m[2][2] *= zScale;
        }

        // angle in radians
        FORCEINLINE void MatrixRotateX(float angle)
        {
            this->MakeIdentity();
            m[1][1] = m[2][2] = static_cast<float>(::cos(angle));
            m[1][2] = static_cast<float>(::sin(angle));
            m[2][1] = static_cast<float>(-::sin(angle));
        }

        // angle in radians
        FORCEINLINE void MatrixRotateY(float angle)
        {
            this->MakeIdentity();
            m[0][0] = m[2][2] = static_cast<float>(::cos(angle));
            m[0][2] = static_cast<float>(-::sin(angle));
            m[2][0] = static_cast<float>(::sin(angle));
        }

        // angle in radians
        FORCEINLINE void MatrixRotateZ(float angle)
        {
            this->MakeIdentity();
            m[0][0] = m[1][1] = static_cast<float>(::cos(angle));
            m[0][1] = static_cast<float>(::sin(angle));
            m[1][0] = static_cast<float>(-::sin(angle));
        }

        // angle in radians
        FORCEINLINE void MatrixRotateYawPitchRoll(float alpha, float beta, float gamma)
        {
            this->MatrixRotateXYZ(beta, alpha, gamma);
        }

        // angle in radians
        FORCEINLINE void MatrixRotateXYZ(float x, float y, float z)
        {
            Matrix4 xMat, yMat, zMat;
            xMat.MakeIdentity(); yMat.MakeIdentity(); zMat.MakeIdentity();

            xMat.MatrixRotateX(x);
            yMat.MatrixRotateY(y);
            zMat.MatrixRotateZ(z);

            *this = (xMat * yMat * zMat);
        }

        [[nodiscard]]
        FORCEINLINE Matrix4 operator+(const Matrix4& otherMat)
        {
            Matrix4 result;
            result.MakeIdentity();

            for (uint32_t rItr = 0; rItr < 4; ++rItr)
            {
                for (uint32_t cItr = 0; cItr < 4; ++cItr)
                {
                    result.m[rItr][cItr] = m[rItr][cItr] + otherMat.m[rItr][cItr];
                }
            }
            return result;
        }

        [[nodiscard]]
        FORCEINLINE Matrix4 operator-(const Matrix4& otherMat)
        {
            Matrix4 result;
            result.MakeIdentity();

            for (uint32_t rItr = 0; rItr < 4; ++rItr)
            {
                for (uint32_t cItr = 0; cItr < 4; ++cItr)
                {
                    result.m[rItr][cItr] = m[rItr][cItr] - otherMat.m[rItr][cItr];
                }
            }
            return result;
        }

        [[nodiscard]]
        FORCEINLINE Matrix4 operator*(const Matrix4& otherMat)
        {
            Matrix4 result;

            for (int itr1 = 0; itr1 < 4; ++itr1)
            {
                for (int itr2 = 0; itr2 < 4; ++itr2)
                {
                    for (int itr3 = 0; itr3 < 4; ++itr3)
                    {
                        result.m[itr1][itr2] += this->m[itr1][itr3] * otherMat.m[itr3][itr2];
                    }
                }
            }
            return result;
        }

        [[nodiscard]]
        FORCEINLINE Matrix4 operator*(const float val)
        {
            Matrix4 result;
            for (uint32_t rItr = 0; rItr < 4; ++rItr)
            {
                for (uint32_t cItr = 0; cItr < 4; ++cItr)
                {
                    result.m[rItr][cItr] = m[rItr][cItr] * val;
                }
            }
            return result;
        }

        [[nodiscard]]
        FORCEINLINE Matrix4 operator/(const float val)
        {
            Matrix4 result;
            for (uint32_t rItr = 0; rItr < 4; ++rItr)
            {
                for (uint32_t cItr = 0; cItr < 4; ++cItr)
                {
                    result.m[rItr][cItr] = m[rItr][cItr] / val;
                }
            }
            return result;
        }

        [[nodiscard]]
        FORCEINLINE Matrix4 MatrixInverse()
        {
            Matrix4 result;

            const float det = this->Determinant();
            const float rDet = 1.0f / det;

            if (det == 0.0f)
            {
                // Inverse matrix doesn't exist. Return an identity
                result = GetIdentity();
            }
            else
            {
                Matrix4 adjoint = this->Adjoint();
                result = adjoint * rDet;
            }
            return result;
        }

        FORCEINLINE void Invert()
        {
            *this = this->MatrixInverse();
        }

        FORCEINLINE void CreatePerspectiveMatrix(float fovY, float aspectRatio, float zNear, float zFar)
        {
            this->MakeIdentity();
            float yScale = static_cast<float>(::cos(fovY / 2.0f) / ::sin(fovY / 2.0f));
            float xScale = yScale / aspectRatio;

            m[0][0] = xScale;
            m[1][1] = yScale;
            m[2][2] = zFar / (zFar - zNear);
            m[2][3] = 1;
            m[3][2] = -zNear * (zFar / (zFar - zNear));
        }

        [[nodiscard]]
        FORCEINLINE Vec4 TransformVector(Vec4 other)
        {
            Vec4 result;
            for (uint32_t itr = 0; itr < 4; ++itr)
            {
                auto vec = GetRowVecAtIndex(itr);
                result[itr] = Dot4(vec, other);
            }
            return result;
        }

        [[nodiscard]]
        FORCEINLINE Vec3 TransformVector(Vec3 other)
        {
            Vec3 result;
            for (uint32_t itr = 0; itr < 3; ++itr)
            {
                Vec3 vec(m[0][itr], m[1][itr], m[2][itr]);
                result[itr] = Dot3(vec, other);
            }
            return result;
        }

        [[nodiscard]]
        FORCEINLINE Vec2 TransformVector(Vec2 other)
        {
            Vec2 result;
            for (uint32_t itr = 0; itr < 2; ++itr)
            {
                Vec2 vec(m[0][itr], m[1][itr]);
                result[itr] = Dot2(vec, other);
            }
            return result;
        }

        float m[4][4];
    };
}