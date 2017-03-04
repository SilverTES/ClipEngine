//------------------------------------------------------------------------------
//--- MugenEngine
//------------------------------------------------------------------------------
#include "Misc.h"

namespace Misc
{
    int random(int beginRange, int endRange)
    {
        return (rand() % endRange) + beginRange;
    }
    VAR pourcent(VAR maxValue, VAR value)
    {
        return (100*value)/maxValue;
    }
    VAR proportion(VAR maxValue, VAR value, VAR range)
    {
        return (range*value)/maxValue;
    }

}
