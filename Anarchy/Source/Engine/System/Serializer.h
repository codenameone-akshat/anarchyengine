#ifndef _SERIALIZER_H_
#define _SERIALIZER_H_

#include <fstream>

#include "boost/archive/binary_oarchive.hpp"

namespace anarchy
{
    class Serializer
    {
    public:
        explicit Serializer(std::string fileName)
            :m_outStream{ fileName },
            m_outArchive{ m_outStream }
        {
        }

        // Writes any object to the provided file. Pointers and References would be dereferenced and written.
        template<typename T>
        inline void Serialize(T&& object)
        {
            m_outArchive << object;
        }

        // Same as the Serialize Function
        template<typename T>
        inline void Write(T&& object)
        {
            Serialize(object);
        }

    private:
        std::string m_fileName = "";
        std::ofstream m_outStream;
        boost::archive::binary_oarchive m_outArchive;
    };

}
#endif // _SERIALIZER_H_