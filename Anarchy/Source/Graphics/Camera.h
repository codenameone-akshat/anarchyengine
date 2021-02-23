#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <Engine/Input/InputHandler.h>
#include <Graphics/D3D12/D3D12GraphicsPSOManager.h>

namespace anarchy
{
    class Camera
    {
        DECLARE_DEFAULT_CLASSMEMBERS(Camera);

    public:
        void HandleInput();
        Matrix4f GetViewMatrix() { return m_viewMatrix; }
        
    private:
        Matrix4f m_viewMatrix = Matrix4f::Identity();
        Vector3f m_cameraPosition = Vector3f(0.0f, 0.0f, -1.0f);
        Vector2f m_cameraRotation = Vector2f::Zero();
        Vector3f m_up = Vector3f::UnitY();
        Vector3f m_right = Vector3f::UnitX();
        Vector3f m_forward = Vector3f::UnitZ();
       
        float32 m_translationSpeedMultiplier = 0.0f;
        float32 m_rotationSpeedMultiplier = 0.0f;

        InputHandler& m_inputHandler = InputHandler::GetInstance();
    };
}

#endif // !_CAMERA_H_
