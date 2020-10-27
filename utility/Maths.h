#ifndef MATHS_H_INCLUDED
#define MATHS_H_INCLUDED
#include "stdafx.h"
#include "Vector2f.h"

constexpr float PI = 3.14159265f;

template <typename T>
T toRadians(T degrees)
{
    return (degrees * PI / 180);
}

template <typename T>
T toDegrees(T radians)
{
    return ((radians * 180) / PI);
}

#endif /* end MATHS_H_INCLUDED */