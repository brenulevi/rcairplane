#include "utils.h"

#include <sstream>

namespace Utils
{
    std::string decToHex(int n)
    {
        std::stringstream ss;
        ss << std::hex << n;
        std::string str = ss.str();
        return str;
    }
}
