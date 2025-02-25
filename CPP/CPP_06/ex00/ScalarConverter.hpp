#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <iostream>
#include <string>

class ScalarConverter
{
private:
    std::string _value; 
public:
    ScalarConverter();
    ScalarConverter(const std::string &src);
    ScalarConverter(ScalarConverter const &src);
    ~ScalarConverter();
    ScalarConverter &operator=(ScalarConverter const &rhs);
    static void convert();
    float toFloat() const; 
    double toDouble() const;
    int toInt() const;
    char toChar() const;
    std::string to_string(const Point& p);
    class ImpossibleException : public std::exception {
        public:
            const char *what() const throw();
    };
    class NonDisplayableException : public std::exception {
        public:
            const char *what() const throw();
    };

};

#endif // SCALARCONVERTER_HPP
