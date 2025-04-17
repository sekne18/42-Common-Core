#include "iter.hpp"
#include <cctype>

template <typename T>
void toUpper(T& str)
{
    int i = -1;
    while (str[++i])
        std::cout << (char)toupper(str[i]);
}

int main( void ) {
    std::string array[5] = {"This ","is ","actually ","awesome ","!!!"}; 

    iter(array, 5, toUpper<std::string>);

    return (0);
}
