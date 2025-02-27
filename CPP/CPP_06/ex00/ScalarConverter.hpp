#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <cstdlib>
#include <sstream>


class ScalarConverter
{
private:
    ScalarConverter(void);
	ScalarConverter(ScalarConverter const &src);
	~ScalarConverter(void);
	ScalarConverter	&operator=(ScalarConverter const &rhs);
    static float toFloat(std::string const &value); 
    static double toDouble(std::string const &value);
    static int toInt(std::string const &value);
    static char toChar(std::string const &value);
    class ImpossibleException : public std::exception {
        public:
            const char *what() const throw();
    };
    class NonDisplayableException : public std::exception {
        public:
            const char *what() const throw();
    };

public:
    static void convert(std::string const &value);

};

#endif // SCALARCONVERTER_HPP
