#ifndef _SCENE_CONSTANT_BUFFER_H_
#define _SCENE_CONSTANT_BUFFER_H_

namespace anarchy
{
    // strictly 16 byte aligned
    struct alignas(16) SceneConstantBuffer
    {
        Vector4f color;
        Matrix4f wvpMatrix;
        Vector4f ambientLight;
        Vector3f lightDirection;

        float32 pad0;
    };
}

#endif // !_SCENE_CONSTANT_BUFFER_H_
