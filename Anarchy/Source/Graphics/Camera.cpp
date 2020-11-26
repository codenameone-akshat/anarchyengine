#include "acpch.h"

#include "Camera.h"
#include <Framework/Math/MathHelper.h>

#define CAM_DAMP_FACTOR 0.12f

namespace anarchy
{
	void Camera::HandleInput()
	{
		if (m_inputHandler.GetIsKeyDown(MOUSE_RBUTTON))
		{
			Vector2i mousePosition = m_inputHandler.GetMousePositionDelta();
			m_cameraRotation.x() += mousePosition.x();
			m_cameraRotation.y() += mousePosition.y();
		}

	}

	void Camera::HandleCameraRotation()
	{
		// default camera properties

	/*	AngleAxisf yawAngle(DegToRad(m_cameraRotation.x() * CAM_DAMP_FACTOR), Vector3d::UnitY());
		AngleAxisf pitchAngle(DegToRad(m_cameraRotation.y() * CAM_DAMP_FACTOR), Vector3d::UnitX());
		AngleAxisf rollAngle(0.0f, Vector3d::UnitZ());
		
		Quaternionf quat = rollAngle * yawAngle * pitchAngle;
		quat.normalize();
		Matrix3f rotation = Matrix3f::Identity();
		rotation = quat.toRotationMatrix();

		Matrix4f transformation = Matrix4f::Identity();*/

	}

	void Camera::HandleCameraTranslation()
	{
	}

}
