#ifndef _TYPES_H_
#define _TYPES_H_

#include <string>

#include "Platform/PlatformConfig.h"

#ifdef USE_EIGEN_LIB
#include <Eigen/Dense_BoostSerialized>
#endif // USE_EIGEN_LIB

#ifdef PLATFORM_WINDOWS
#include <wrl.h>
#endif // PLATFORM_WINDOWS

namespace anarchy
{
	// byte
	using byte				= std::byte;

	// unsigned int
	using uint8				= std::uint8_t;
	using uint16			= std::uint16_t;
	using uint32			= std::uint32_t;
	using uint64			= std::uint64_t;

	// signed int			  
	using int8				= std::int8_t;
	using int16				= std::int16_t;
	using int32				= std::int32_t;
	using int64				= std::int64_t;

	// floating point
	using float32			= float;
	using float64			= double;

	// string | char types
	using wchar				= wchar_t;
	using string			= std::string;
	using wstring			= std::wstring;
	using cstring			= char*;

	// string stream
	using ostringstream		= std::ostringstream;
	using istringstream		= std::istringstream;
	using stringstream		= std::stringstream;

	using wostringstream	= std::wostringstream;
	using wistringstream	= std::wistringstream;
	using wstringstream		= std::wstringstream;

	// typeless
	using voidptr			= void*;
	using handle			= void*;

#ifdef PLATFORM_WINDOWS
	template<typename T>
	using ComPtr			= Microsoft::WRL::ComPtr<T>;
#endif // PLATFORM_WINDOWS

	// Math
#ifdef USE_EIGEN_LIB
	// Vectors 
	using Vector2i			= Eigen::Vector2i;
	using Vector2f			= Eigen::Vector2f;
	using Vector2d			= Eigen::Vector2d;

	using Vector3i			= Eigen::Vector3i;
	using Vector3f			= Eigen::Vector3f;
	using Vector3d			= Eigen::Vector3d;

	using Vector4i			= Eigen::Vector4i;
	using Vector4f			= Eigen::Vector4f;
	using Vector4d			= Eigen::Vector4d;

	// Column Major Matrices
	// Matrix 2x2 | Matrix 2xN | Matrix Nx2
	using Matrix2i			= Eigen::Matrix<int32, 2, 2, Eigen::ColMajor>;
	using Matrix2f			= Eigen::Matrix<float32, 2, 2, Eigen::ColMajor>;
	using Matrix2d			= Eigen::Matrix<float64, 2, 2, Eigen::ColMajor>;
	
	using Matrix2Xi			= Eigen::Matrix<int32, 2, -1, Eigen::ColMajor>;
	using Matrix2Xf			= Eigen::Matrix<float32, 2, -1, Eigen::ColMajor>;
	using Matrix2Xd			= Eigen::Matrix<float64, 2, -1, Eigen::ColMajor>;
	
	using MatrixX2i			= Eigen::Matrix<int32, -1, 2, Eigen::ColMajor>;
	using MatrixX2f			= Eigen::Matrix<float32, -1, 2, Eigen::ColMajor>;
	using MatrixX2d			= Eigen::Matrix<float64, -1, 2, Eigen::ColMajor>;

	// Matrix 3x3 | Matrix 3xN | Matrix Nx3
	using Matrix3i			= Eigen::Matrix<int32, 3, 3, Eigen::ColMajor>;
	using Matrix3f			= Eigen::Matrix<float32, 3, 3, Eigen::ColMajor>;
	using Matrix3d			= Eigen::Matrix<float64, 3, 3, Eigen::ColMajor>;

	using Matrix3Xi			= Eigen::Matrix<int32, 3, -1, Eigen::ColMajor>;
	using Matrix3Xf			= Eigen::Matrix<float32, 3, -1, Eigen::ColMajor>;
	using Matrix3Xd			= Eigen::Matrix<float64, 3, -1, Eigen::ColMajor>;
	
	using MatrixX3i			= Eigen::Matrix<int32, -1, 3, Eigen::ColMajor>;
	using MatrixX3f			= Eigen::Matrix<float32, -1, 3, Eigen::ColMajor>;
	using MatrixX3d			= Eigen::Matrix<float64, -1, 3, Eigen::ColMajor>;

	// Matrix 4x4 | Matrix 4xN | Matrix Nx4
	using Matrix4i			= Eigen::Matrix<int32, 4, 4, Eigen::ColMajor>;
	using Matrix4f			= Eigen::Matrix<float32, 4, 4, Eigen::ColMajor>;
	using Matrix4d			= Eigen::Matrix<float64, 4, 4, Eigen::ColMajor>;
	
	using Matrix4Xi			= Eigen::Matrix<int32, 4, -1, Eigen::ColMajor>;
	using Matrix4Xf			= Eigen::Matrix<float32, 4, -1, Eigen::ColMajor>;
	using Matrix4Xd			= Eigen::Matrix<float64, 4, -1, Eigen::ColMajor>;
	
	using MatrixX4i			= Eigen::Matrix<int32, -1, 4, Eigen::ColMajor>;
	using MatrixX4f			= Eigen::Matrix<float32, -1, 4, Eigen::ColMajor>;
	using MatrixX4d			= Eigen::Matrix<float64, -1, 4, Eigen::ColMajor>;

	// Quaternions
	using Quaternionf		= Eigen::Quaternionf;
	using Quaterniond		= Eigen::Quaterniond;

	// Angle Axis
	using AngleAxisf		= Eigen::AngleAxisf;
	using AngleAxisd		= Eigen::AngleAxisd;

	// Affine Transforms
	using Affine2f			= Eigen::Affine2f;
	using Affine2d			= Eigen::Affine2d;
	using Affine3f			= Eigen::Affine3f;
	using Affine3d			= Eigen::Affine3d;
#endif // USE_EIGEN_LIB

}
#endif // !_TYPES_H_