#ifndef _VERTEX_LAYOUT_H_
#define _VERTEX_LAYOUT_H_

#include <Framework/SerializationHelpers.h>

namespace anarchy
{
    struct VertexLayout
    {
        Vector3f position;
        Vector3f normal;
        
        SERIALIZATION_PRIVATE_IMPL_ENABLE;
        SERIALIZE_IMPL()
        {
            SERIALIZE_PROPERTY(position);
            SERIALIZE_PROPERTY(normal);
        }
    };
}

#endif // !_VERTEX_LAYOUT_H_
