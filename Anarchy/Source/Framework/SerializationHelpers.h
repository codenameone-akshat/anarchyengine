#ifndef _SERIALIZATION_HELPERS_H_
#define _SERIALIZATION_HELPERS_H_

namespace anarchy
{
#define SERIALIZATION_PRIVATE_IMPL_ENABLE friend class boost::serialization::access;

#define SERIALIZE_MEMBER(x) ar & x

#define SERIALIZE_PROPERTY(x) ar & x

#define SERIALIZE_IMPL() template <typename Archive> void serialize(Archive& ar, const unsigned int version)

// std includes for serialize() overrides
#define SERIALIZE_STD_VECTOR_INCLUDE            <boost/serialization/vector.hpp>
#define SERIALIZE_STD_ARRAY_INCLUDE             <boost/serialization/array.hpp>
#define SERIALIZE_STD_STRING_INCLUDE            <boost/serialization/string.hpp>
#define SERIALIZE_STD_MAP_INCLUDE               <boost/serialization/map.hpp>
#define SERIALIZE_STD_UNORDEREDMAP_INCLUDE      <boost/serialization/unordered_map.hpp>
#define SERIALIZE_STD_SHAREDPTR_INCLUDE        <boost/serialization/shared_ptr.hpp>
#define SERIALIZE_ACCESS_INCLUDE                <boost/serialization/access.hpp>
}

#endif // _SERIALIZATION_HELPERS_H_
