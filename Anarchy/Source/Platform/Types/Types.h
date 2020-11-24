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

	// Matrix 2x2 | Matrix 2xN | Matrix Nx2
	using Matrix2i			= Eigen::Matrix2i;
	using Matrix2f			= Eigen::Matrix2f;
	using Matrix2d			= Eigen::Matrix2d;
	
	using Matrix2Xi			= Eigen::Matrix2Xi;
	using Matrix2Xf			= Eigen::Matrix2Xf;
	using Matrix2Xd			= Eigen::Matrix2Xd;
	
	using MatrixX2i			= Eigen::MatrixX2i;
	using MatrixX2f			= Eigen::MatrixX2f;
	using MatrixX2d			= Eigen::MatrixX2d;

	// Matrix 3x3 | Matrix 3xN | Matrix Nx3
	using Matrix3i			= Eigen::Matrix3i;
	using Matrix3f			= Eigen::Matrix3f;
	using Matrix3d			= Eigen::Matrix3d;

	using Matrix3Xi			= Eigen::Matrix3Xi;
	using Matrix3Xf			= Eigen::Matrix3Xf;
	using Matrix3Xd			= Eigen::Matrix3Xd;
	
	using MatrixX3i			= Eigen::MatrixX3i;
	using MatrixX3f			= Eigen::MatrixX3f;
	using MatrixX3d			= Eigen::MatrixX3d;

	// Matrix 4x4 | Matrix 4xN | Matrix Nx4
	using Matrix4i			= Eigen::Matrix4i;
	using Matrix4f			= Eigen::Matrix4f;
	using Matrix4d			= Eigen::Matrix4d;
	
	using Matrix4Xi			= Eigen::Matrix4Xi;
	using Matrix4Xf			= Eigen::Matrix4Xf;
	using Matrix4Xd			= Eigen::Matrix4Xd;
	
	using MatrixX4i			= Eigen::MatrixX4i;
	using MatrixX4f			= Eigen::MatrixX4f;
	using MatrixX4d			= Eigen::MatrixX4d;
#endif // USE_EIGEN_LIB

}
#endif // !_TYPES_H_