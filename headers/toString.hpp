#ifndef TOSTRING_INCLUDED
#define TOSTRING_INCLUDED

#include <sstream>
template <typename T> inline std::string toString(T dat)
{
    std::ostringstream oss;
    oss << dat;
    return oss.str();
}

#endif // TOSTRING_INCLUDED
