#include "acpch.h"

#include "Camera.h"
#include <Framework/Math/MathHelper.h>

#define CAM_DAMP_FACTOR 0.12f

namespace anarchy
{
	void Camera::HandleInput()
	{
		// Rotation
		if (m_inputHandler.GetIsKeyDown(MOUSE_RBUTTON))
		{
			Vector2i mousePosition = m_inputHandler.GetMousePositionDelta();
			m_cameraRotation.x += mousePosition.x;
			m_cameraRotation.y += mousePosition.y;
		}

		// Translation
		if (m_inputHandler.GetIsKeyDown(KEY_W))
		{
			m_cameraPosition.z += 1.0f;
		}
		
		if (m_inputHandler.GetIsKeyDown(KEY_A))
		{
			m_cameraPosition.x -= 1.0f;
		}
		
		if (m_inputHandler.GetIsKeyDown(KEY_S))
		{
			m_cameraPosition.z -= 1.0f;
		}
		
		if (m_inputHandler.GetIsKeyDown(KEY_D))
		{
			m_cameraPosition.x += 1.0f;
		}
		
		if (m_inputHandler.GetIsKeyDown(KEY_Q))
		{
			m_cameraPosition.y -= 1.0f;
		}
		
		if (m_inputHandler.GetIsKeyDown(KEY_E))
		{
			m_cameraPosition.y += 1.0f;
		}

		//// default camera properties
		const float32 dampedDegRotx = DegToRadf(m_cameraRotation.x * CAM_DAMP_FACTOR);
		const float32 dampedDegRoty = DegToRadf(m_cameraRotation.y * CAM_DAMP_FACTOR);
		
		Matrix4f rotMat;
		rotMat.RotateYawPitchRoll(dampedDegRotx, dampedDegRoty, 0.0f);

		Vector4f forward(Vector4f::Init_Flags::Init_UnitZ);
		Vector4f up		(Vector4f::Init_Flags::Init_UnitY);
		Vector4f right	(Vector4f::Init_Flags::Init_UnitX);

		// align normals to rot matrix
		forward = rotMat.TransformVector(forward);
		up		= rotMat.TransformVector(up);
		right	= rotMat.TransformVector(right);

		Matrix4f translationMat;
		translationMat.Translate(m_cameraPosition.x, m_cameraPosition.y, m_cameraPosition.z);

		m_viewMatrix = rotMat * translationMat;
		m_viewMatrix.Invert();
	}
}
