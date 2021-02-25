#ifndef _MATH_HELPER_H_
#define _MATH_HELPER_H_

namespace anarchy
{
#define MATH_PI 3.14159265358979323846
#define DegToRad(degree) ((degree) * (MATH_PI / 180.0f))
#define DegToRadf(degree) static_cast<float>(((degree) * (MATH_PI / 180.0f)))
}

#endif // !_MATH_HELPER_H_
