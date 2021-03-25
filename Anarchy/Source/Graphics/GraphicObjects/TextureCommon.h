#ifndef _TEXTURE_COMMON_H_
#define _TEXTURE_COMMON_H_

namespace anarchy
{
    enum class TextureType : uint32
    {
        Diffuse,
        Normal,
        Rougheness,
        Opacity,
        _Count
    };

    struct TextureDimensions
    {
        uint64 width;
        uint64 height;
        uint64 depth;

        SERIALIZE_IMPL()
        {
            SERIALIZE_MEMBER(width);
            SERIALIZE_MEMBER(height);
            SERIALIZE_MEMBER(depth);
        }
    };
}

#endif // !_TEXTURE_COMMON_H_
