//------------------------------------------------------------------------------
//--- MugenEngine
//------------------------------------------------------------------------------
#include <iostream>

template <class M, class E>
E mlog(M msg, E error)
{
#ifdef SHOW_LOG
    std::cout << msg;
#endif // SHOW_LOG
    return error;
}

