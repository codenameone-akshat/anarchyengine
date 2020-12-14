#ifndef _MATRIX_4_HPP_
#define _MATRIX_4_HPP_

#ifdef ANARCHY_MATH_ENABLE

#ifndef FORCEINLINE
#define FORCEINLINE __forceinline
#endif // !FORCEINLINE

#include <cassert>

#ifndef NativeAssert
#define NativeAssert(cond, message) assert(cond)
#endif // !NativeAssert

#include <Framework/SerializationHelpers.h>
#include <Framework/Math/Vector4.hpp>
#include <Framework/Math/Vector3.hpp>
#include <Framework/Math/Vector2.hpp>

namespace anarchy::math
{
	template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
	struct Matrix4
	{
		enum class Init_Flags
		{
			Init_Zero,
			Init_Identity
		};

		Matrix4(Init_Flags flags = Init_Flags::Init_Identity)
		{
			switch (flags)
			{
			case Init_Flags::Init_Identity: SetIdentity();
				break;
			case Init_Flags::Init_Zero: SetZero();
				break;
			default: NativeAssert(false, "Undefined Flag");
				break;
			}
		}

		~Matrix4()
		{
		}
		
		SERIALIZE_IMPL()
		{
			SERIALIZE_MEMBER(m); // hope this works
		}

		FORCEINLINE void SetIdentity()
		{
			SetZero();
			m00 = m11 = m22 = m33 = (T)1;
		}

		FORCEINLINE void SetZero()
		{
			std::memset(m, 0, sizeof(m));
		}

		FORCEINLINE void Transpose()
		{
			Matrix4<T> result;
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
		FORCEINLINE Vector4<T> GetRowAtIndex(uint32_t idx) const
		{
			NativeAssert(idx < 4, "Vector4 Requested Index > 4");

			Vector4<T> row;
			memcpy(&row, &m[idx][0], sizeof(Vector4<T>));
			return row;
		}

		[[nodiscard]]
		FORCEINLINE Vector4<T> GetColumnAtIndex(uint32_t idx) const
		{
			NativeAssert(idx < 4, "Vector4 Requested Index > 4");

			Vector4<T> col = Vector4<T>(m[0][idx], m[1][idx], m[2][idx], m[3][idx]);
			return col;
		}

		[[nodiscard]]
		FORCEINLINE static Matrix4<T> Transposed(Matrix4<T> otherMat)
		{
			otherMat.Transpose();
			return otherMat;
		}

		[[nodiscard]]
		FORCEINLINE static Matrix4<T> Identity()
		{
			Matrix4<T> mIdentity(Init_Flags::Init_Identity);
			return mIdentity;
		}

		[[nodiscard]]
		FORCEINLINE static Matrix4<T> Zero()
		{
			Matrix4<T> mZero(Init_Flags::Init_Zero);
			return mZero;
		}

		[[nodiscard]]
		FORCEINLINE T Trace()
		{
			// Sum of the main diagonal
			return (m00 + m11 + m22 + m33);
		}

		FORCEINLINE float Determinant()
		{
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
			return (
				m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) -
				m[1][0] * (m[0][1] * m[2][2] - m[0][2] * m[2][1]) +
				m[2][0] * (m[0][1] * m[1][2] - m[0][2] * m[1][1])
				);
		}

		FORCEINLINE Matrix4<T> Adjoint()
		{
			Matrix4<T> adjoint;

			// Calculate Cofactor Matrix
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
			
			adjoint.Transpose();
			return adjoint;
		}

		FORCEINLINE void Translate(const float x, const float y, const float z)
		{
			m[3][0] += x;
			m[3][1] += y;
			m[3][2] += z;
		}

		FORCEINLINE void ScaleUniform(const float scale)
		{
			m[0][0] *= scale;
			m[1][1] *= scale;
			m[2][2] *= scale;
		}

		FORCEINLINE void Scale(const float xScale, const float yScale, const float zScale)
		{
			m[0][0] *= xScale;
			m[1][1] *= yScale;
			m[2][2] *= zScale;
		}

		// angle in radians
		FORCEINLINE void RotateX(float angle)
		{
			this->SetIdentity();
			m[1][1] = m[2][2] = static_cast<float>(::cos(angle));
			m[1][2] = static_cast<float>(::sin(angle));
			m[2][1] = static_cast<float>(-::sin(angle));
		}

		// angle in radians
		FORCEINLINE void RotateY(float angle)
		{
			this->SetIdentity();
			m[0][0] = m[2][2] = static_cast<float>(::cos(angle));
			m[0][2] = static_cast<float>(-::sin(angle));
			m[2][0] = static_cast<float>(::sin(angle));
		}

		// angle in radians
		FORCEINLINE void RotateZ(float angle)
		{
			this->SetIdentity();
			m[0][0] = m[1][1] = static_cast<float>(::cos(angle));
			m[0][1] = static_cast<float>(::sin(angle));
			m[1][0] = static_cast<float>(-::sin(angle));
		}

		// angle in radians
		FORCEINLINE void RotateYawPitchRoll(float yaw, float pitch, float roll)
		{
			this->RotateXYZ(pitch, yaw, roll);
		}

		// angle in radians
		FORCEINLINE void RotateXYZ(float x, float y, float z)
		{
			Matrix4<T> xMat, yMat, zMat;

			xMat.RotateX(x);
			yMat.RotateY(y);
			zMat.RotateZ(z);

			*this = (xMat * yMat * zMat);
		}

		[[nodiscard]]
		FORCEINLINE Matrix4<T> operator+(const Matrix4<T>& otherMat)
		{
			Matrix4<T> result;
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
		FORCEINLINE Matrix4<T> operator-(const Matrix4& otherMat)
		{
			Matrix4<T> result;
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
		FORCEINLINE Matrix4<T> operator*(const Matrix4<T>& otherMat)
		{
			Matrix4<T> result;
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
		FORCEINLINE Matrix4<T> operator*(const float val)
		{
			Matrix4<T> result;
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
		FORCEINLINE Matrix4<T> operator/(const float val)
		{
			Matrix4<T> result;
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
		FORCEINLINE Matrix4<T> Inverse()
		{
			Matrix4<T> result;
			const float det = this->Determinant();

			// If the inverse matrix doesn't exist. Return an identity
			if (det != 0.0f)
			{
				Matrix4<T> adjoint = this->Adjoint();
				const float rDet = 1.0f / det;
				result = adjoint * rDet;
			}
			
			return result;
		}

		FORCEINLINE void Invert()
		{
			*this = this->Inverse();
		}

		FORCEINLINE void CreatePerspectiveMatrix(float fovY, float aspectRatio, float zNear, float zFar)
		{
			this->SetIdentity();
			float yScale = static_cast<float>(::cos(fovY / 2.0f) / ::sin(fovY / 2.0f));
			float xScale = yScale / aspectRatio;

			m[0][0] = xScale;
			m[1][1] = yScale;
			m[2][2] = zFar / (zFar - zNear);
			m[2][3] = 1;
			m[3][2] = -zNear * (zFar / (zFar - zNear));
		}

		[[nodiscard]]
		FORCEINLINE Vector4<T> TransformVector(Vector4<T> other)
		{
			Vector4<T> result;
			for (uint32_t itr = 0; itr < 4; ++itr)
			{
				Vector4<T> vec = GetColumnAtIndex(itr);
				result[itr] = Vector4<T>::Dot4(vec, other);
			}
			return result;
		}

		[[nodiscard]]
		FORCEINLINE Vector3<T> TransformVector(Vector3<T> other)
		{
			Vector3<T> result;
			for (uint32_t itr = 0; itr < 3; ++itr)
			{
				Vector3<T> vec(m[0][itr], m[1][itr], m[2][itr]);
				result[itr] = Vector3<T>::Dot3(vec, other);
			}
			return result;
		}

		[[nodiscard]]
		FORCEINLINE Vector2<T> TransformVector(Vector2<T> other)
		{
			Vector2<T> result;
			for (uint32_t itr = 0; itr < 2; ++itr)
			{
				Vector2<T> vec(m[0][itr], m[1][itr]);
				result[itr] = Vector2<T>::Dot2(vec, other);
			}
			return result;
		}

		union 
		{
			struct
			{
				T m00, m01, m02, m03; // m[0]
				T m10, m11, m12, m13; // m[1]
				T m20, m21, m22, m23; // m[2]
				T m30, m31, m32, m33; // m[3]
			};

			struct 
			{
				T m0[4];
				T m1[4];
				T m2[4];
				T m3[4];
			};

			T m[4][4];
		};
	};
}

#endif // ANARCHY_MATH_ENABLE

#endif // !_MATRIX_4_HPP_
