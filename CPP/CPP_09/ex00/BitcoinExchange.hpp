#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <map>

class BitcoinExchange
{
private:
    std::map<std::string, float> _data; // Map to store date and value pairs
    std::string _inputFile; // Input file name
    class TooLargeException : public std::exception {
        public:
            const char *what() const throw();
    };
    class NotPositiveException : public std::exception {
        public:
            const char *what() const throw();
    };
    class BadInputException : public std::exception {
        std::string _msg;
        public:
            BadInputException(const std::string& msg);
            virtual ~BadInputException() throw();
            virtual const char *what() const throw();
    };
    std::string findDate(std::string date);
    void print_data();
    bool valid_date(std::string date);
    bool valid_value(std::string value, std::string date);
    void calcValues(std::string date, float values);
    void loadDatabase();



public:
    BitcoinExchange(std::string inputFile);
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange &src);
    BitcoinExchange &operator=(const BitcoinExchange &other);
    ~BitcoinExchange();
    void processFile();

};

#endif // BITCOINEXCHANGE_HPP
