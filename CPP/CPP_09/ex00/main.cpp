#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }
    BitcoinExchange bitcoinExchange(argv[1]);
    bitcoinExchange.processFile();
    return 0;
}
