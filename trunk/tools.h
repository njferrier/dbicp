#ifndef TOOLS_H
#define TOOLS_H

#include <sstream>

/*****************************************
*            TOOL FUNCTIONS              *
******************************************/

template <class T>
inline std::string to_string (const T& t)
{
        std::stringstream ss;
        ss << t;
        return ss.str();
}

#endif
