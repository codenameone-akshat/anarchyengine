#ifndef _CAMERA_COMPONENT_H_
#define _CAMERA_COMPONENT_H_

namespace anarchy
{
    class BaseCamera
    {
        DECLARE_DEFAULT_CLASSMEMBERS(BaseCamera);
        DECLARE_DEFAULT_PROPERTY(Matrix4f, projection, Projection);
    };

    class CameraComponent
    {
        DECLARE_DEFAULT_CLASSMEMBERS(CameraComponent);

    public:
        BaseCamera camera;
    };
}

#endif // !_CAMERA_COMPONENT_H_ 
