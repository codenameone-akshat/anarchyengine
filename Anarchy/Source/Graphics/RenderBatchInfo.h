#ifndef _RENDER_BATCH_INFO_H_

#include <Framework/SerializationHelpers.h>

namespace anarchy
{
    struct RenderBatchInfo
    {
        uint64 indexCount = 0;
        uint64 vertexCount = 0;
        uint64 startIndex = 0;
        uint64 startVertex = 0;
        uint64 startInstance = 0;

        SERIALIZATION_PRIVATE_IMPL_ENABLE;
        SERIALIZE_IMPL()
        {
            SERIALIZE_PROPERTY(indexCount);
            SERIALIZE_PROPERTY(vertexCount);
            SERIALIZE_PROPERTY(startIndex);
            SERIALIZE_PROPERTY(startVertex);
            SERIALIZE_PROPERTY(startInstance);
        }
    };
}

#endif // !_RENDER_BATCH_INFO_H_
