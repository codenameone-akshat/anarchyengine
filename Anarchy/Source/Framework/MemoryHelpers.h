#ifndef _MEMORY_HELPERS_H_
#define _MEMORY_HELPERS_H_

// Works only on power of 2 alignments
#define AlignTo(num, align) \
    (((num) + ((align) - 1)) & ~((align) - 1))

#ifndef ZeroMemory // in case of linux
#define ZeroMemory(Destination,Length) memset((Destination),0,(Length))
#endif // !ZeroMemory


#endif // !_MEMORY_HELPERS_H_
