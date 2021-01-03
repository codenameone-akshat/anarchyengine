#include "acpch.h"

#include "Camera.h"
#include <Framework/Math/MathHelper.h>
#include <Graphics/GfxControllables.h>

namespace anarchy
{
	void Camera::HandleInput()
	{
		// Controllable's Update
        m_translationSpeedMultiplier = GfxControllables::GetCamTranslationSpeedMult();
        m_rotationSpeedMultiplier = GfxControllables::GetCamRotationSpeedMult();

		// Rotation
		if (m_inputHandler.GetIsKeyDown(MOUSE_RBUTTON))
		{
			Vector2i mousePosition = m_inputHandler.GetMousePositionDelta();
			m_cameraRotation.x += mousePosition.x;
			m_cameraRotation.y += mousePosition.y;
		}

		//// default camera properties
		const float32 dampedDegRotx = DegToRadf(m_cameraRotation.x * m_rotationSpeedMultiplier);
		const float32 dampedDegRoty = DegToRadf(m_cameraRotation.y * m_rotationSpeedMultiplier);

		Matrix4f rotMat;
		rotMat.RotateYawPitchRoll(dampedDegRotx, dampedDegRoty, 0.0f);

		Vector4f forward(Vector4f::Init_Flags::Init_UnitZ);
		Vector4f up(Vector4f::Init_Flags::Init_UnitY);
		Vector4f right(Vector4f::Init_Flags::Init_UnitX);

		// align normals to rot matrix
		forward = rotMat.TransformVector(forward);
		up = rotMat.TransformVector(up);
		right = rotMat.TransformVector(right);

		forward.Normalize();
		up.Normalize();
		right.Normalize();

		// Translation
		if (m_inputHandler.GetIsKeyDown(KEY_W))
		{
			m_cameraPosition += (forward * m_translationSpeedMultiplier);
		}
		
		if (m_inputHandler.GetIsKeyDown(KEY_A))
		{
			m_cameraPosition -= (right * m_translationSpeedMultiplier);
		}
		
		if (m_inputHandler.GetIsKeyDown(KEY_S))
		{
			m_cameraPosition -= (forward * m_translationSpeedMultiplier);
		}
		
		if (m_inputHandler.GetIsKeyDown(KEY_D))
		{
			m_cameraPosition += (right * m_translationSpeedMultiplier);
		}
		
		if (m_inputHandler.GetIsKeyDown(KEY_Q))
		{
			m_cameraPosition -= (up * m_translationSpeedMultiplier);
		}
		
		if (m_inputHandler.GetIsKeyDown(KEY_E))
		{
			m_cameraPosition += (up * m_translationSpeedMultiplier);
		}

		Matrix4f translationMat;
		translationMat.Translate(m_cameraPosition.x, m_cameraPosition.y, m_cameraPosition.z);

		m_viewMatrix = rotMat * translationMat;
		m_viewMatrix.Invert();
	}
}
