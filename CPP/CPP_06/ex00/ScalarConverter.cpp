#include "ScalarConverter.hpp"

char ScalarConverter::toChar(std::string const &value)
{
  if (value.length() == 1 && std::isprint(value[0]) && std::isalpha(value[0]))
    return value[0];

  int i = toInt(value);
  if (i < 0 || i > 127)
    throw ScalarConverter::ImpossibleException();
  char c = static_cast<char>(i);
  if (!std::isprint(c))
    throw ScalarConverter::NonDisplayableException();
  return c;
}

int ScalarConverter::toInt(std::string const &value)
{
  long i;
  char* endptr;

  if (value == "0")
    return 0;
  i = std::strtol(value.c_str(), &endptr, 10);
  if ((*endptr) || value.c_str() == endptr)
    throw ScalarConverter::ImpossibleException();
  if (value == "nan" || value == "NaN" || value == "inf" || value == "-inf")
    throw ScalarConverter::ImpossibleException();
  if (i <= INT_MAX && i >= INT_MIN)
    return static_cast<int>(i);
  throw ScalarConverter::ImpossibleException();
}

float ScalarConverter::toFloat(std::string const &value)
{
  float f;
  char* endptr;

  f = std::strtof(value.c_str(), &endptr);
  if (!(*endptr) || (!endptr[1] && *endptr == 'f'))
    return f;
  else
    throw ScalarConverter::ImpossibleException();
}

double ScalarConverter::toDouble(std::string const &value)
{
  double d;
  char* endptr;

  d = std::strtod(value.c_str(), &endptr);
  if (!(*endptr) || (!endptr[1] && *endptr == 'f'))
    return d;
  else
    throw ScalarConverter::ImpossibleException();
}

const char *ScalarConverter::ImpossibleException::what() const throw()
{
  return "impossible";
}

const char *ScalarConverter::NonDisplayableException::what() const throw()
{
  return "Non displayable";
}

void ScalarConverter::convert(std::string const &value)
{
  try {
    std::cout << "char: ";
    std::cout << toChar(value) << std::endl;
  } catch (ScalarConverter::ImpossibleException &e) {
    std::cout << e.what() << std::endl;
  } catch (ScalarConverter::NonDisplayableException &e) {
    std::cout << e.what() << std::endl;
  }
  try {
    std::cout << "int: ";
    std::cout << toInt(value) << std::endl;
  } catch (ScalarConverter::ImpossibleException &e) {
    std::cout << e.what() << std::endl;
  }
  try {
    std::cout << "float: ";
    std::cout << std::fixed << std::setprecision(1) << toFloat(value) << "f" << std::endl;
  } catch (ScalarConverter::ImpossibleException &e) {
    std::cout << e.what() << std::endl;
  }
  try {
    std::cout << "double: ";
    std::cout << std::fixed << std::setprecision(1) << toDouble(value) << std::endl;
  } catch (ScalarConverter::ImpossibleException &e) {
    std::cout << e.what() << std::endl;
  }
}
