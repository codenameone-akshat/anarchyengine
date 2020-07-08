#ifndef _DESERIALIZER_H_
#define _DESERIALIZER_H_

#include <fstream>

#include "boost/archive/binary_iarchive.hpp"

namespace anarchy::system
{
    // Reader Class using Boost Binary Archive
    class DeSerializer
    {
    public:
        explicit DeSerializer(std::string fileName)
            :m_inStream{ fileName },
            m_inArchive{ m_inStream }
        {
        }

        // Reads any object to the provided file. Make sure to keep the order same as when it was serialized
        template<typename T>
        inline void DeSerialize(T& object)
        {
            m_inArchive >> object;
        }

        // Same as the DeSerialize Function
        template<typename T>
        inline void Read(T& object)
        {
            DeSerialize(object);
        }

    private:
        std::string m_fileName = "";
        std::ifstream m_inStream;

}
#endif // _DESERIALIZER_H_