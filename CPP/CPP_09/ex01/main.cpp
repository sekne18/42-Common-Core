#include "RPN.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Missing arguments." << std::endl;
        return (1);
    }
    RPN rpn;
    rpn.processInput(argv[1]);
    return (0);
}
