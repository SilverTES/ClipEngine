//------------------------------------------------------------------------------
//--- MugenEngine
//------------------------------------------------------------------------------
#ifndef MISC_H_INCLUDED
#define MISC_H_INCLUDED

//#define NOMINMAX // Avoid Visual Studio 2015 error std::min/max

#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>
#include <cmath>

using VAR = float;

template <class M = std::string, class E = int>
static E mlog(M msg, E error = 0);

namespace Misc
{
    int random(int beginRange, int endRange);

    float pourcent(VAR maxValue, VAR value);
    float proportion(VAR maxValue, VAR value, VAR range);
}

#include "Misc.inl"


#endif // MISC_H_INCLUDED
