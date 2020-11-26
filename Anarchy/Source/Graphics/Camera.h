#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <Engine/Input/InputHandler.h>

namespace anarchy
{
	class Camera
	{
		DECLARE_DEFAULT_CLASSMEMBERS(Camera);
	
	public:
		void HandleInput();
		
	private:
		void HandleCameraRotation();
		void HandleCameraTranslation();

		Matrix4f m_viewMatrix = Matrix4f::Identity();
		Vector3f m_cameraPosition = Vector3f(0.0f, 1.0f, 0.0f);
		Vector2f m_cameraRotation = Vector2f::Zero();
		Vector3f m_up = Vector3f::UnitY();
		Vector3f m_right = Vector3f::UnitX();
		Vector3f m_forward = Vector3f::UnitZ();

		InputHandler& m_inputHandler = InputHandler::GetInstance();
	};
}

#endif // !_CAMERA_H_
