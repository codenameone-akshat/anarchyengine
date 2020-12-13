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
		//const float32 dampedDegRotx = DegToRadf(m_cameraRotation.x * CAM_DAMP_FACTOR);
		//const float32 dampedDegRoty = DegToRadf(m_cameraRotation.y * CAM_DAMP_FACTOR);

		//const Affine3f pitch = Affine3f(AngleAxisf(dampedDegRotx, Vector3f::UnitX()));
		//const Affine3f yaw = Affine3f(AngleAxisf(dampedDegRoty, Vector3f::UnitY()));
		//const Affine3f roll = Affine3f(AngleAxisf(0.0f, Vector3f::UnitZ()));

		//const Affine3f rotMatrix = roll * yaw * pitch;

		//const Vector3f transVec(m_cameraPosition.x, m_cameraPosition.y, m_cameraPosition.z);
		//const Affine3f translation = Affine3f(Translation3f(transVec));

		//const Affine3f affineTransform = translation * rotMatrix;
		//const Matrix4f transform = affineTransform.matrix();

		//m_viewMatrix = transform;
		//m_viewMatrix = m_viewMatrix.inverse();
	}
}
