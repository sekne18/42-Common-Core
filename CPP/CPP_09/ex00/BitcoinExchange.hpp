#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

class BitcoinExchange
{
private:
    std::map<std::string, float> _data; // Map to store date and value pairs
    std::string _inputFile; // Input file name
    void validateDate(const std::string &date);
    void validateValue(const std::string &value);
    void processLine(const std::string &line);
    void printResult(const std::string &date, float value);

public:
    BitcoinExchange(const std::string &inputFile);
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange &src);
    BitcoinExchange &operator=(const BitcoinExchange &rhs);
    ~BitcoinExchange();
    void processFile();

};

#endif // BITCOINEXCHANGE_HPP
