#include "log.h"

namespace limos
{

int log(int type, const char *str)
{
    if (type == NO_ERR) {
        std::cout << "Log: " << str << "\n";
    } else if (type == ERR) {
        std::cout << "Error: " << str << "\n";
    }
    
    return type;
}

}