#include "ScalarConverter.hpp"

char ScalarConverter::toChar(std::string const &value)
{
  if (value.length() == 1 && std::isprint(value[0]) && std::isalpha(value[0]))
    return value[0];

  try {
    int i = toInt(value);
    if (i < 0 || i > 127)
      throw ScalarConverter::ImpossibleException();
    char c = static_cast<char>(i);
    if (!std::isprint(c))
      throw ScalarConverter::NonDisplayableException();
    return c;
  } catch (std::exception &e) {
    throw ScalarConverter::ImpossibleException();
  }
}

int ScalarConverter::toInt(std::string const &value)
{
  long i;
  char* endptr;

  try {
    i = std::strtol(value.c_str(), &endptr, 10);
    if (endptr == value.c_str() || i > INT_MAX || i < INT_MIN || *endptr != '\0') {
      throw ScalarConverter::ImpossibleException();
    }
  } catch (std::exception &e) {
    throw ScalarConverter::ImpossibleException();
  }
  return static_cast<int>(i);
}

float ScalarConverter::toFloat(std::string const &value)
{
  float f;
  char* endptr;
  
  try {
    f = std::strtof(value.c_str(), &endptr);
    if (endptr == value.c_str() || *endptr != '\0')
      throw ScalarConverter::ImpossibleException();
  } catch (std::exception &e) {
    throw ScalarConverter::ImpossibleException();
  }
  return f;
}

double ScalarConverter::toDouble(std::string const &value)
{
  double d;
  char* endptr;

  try {
    d = std::strtod(value.c_str(), &endptr);
    if (endptr == value.c_str() || *endptr != '\0')
      throw ScalarConverter::ImpossibleException();
  } catch (std::exception &e) {
    throw ScalarConverter::ImpossibleException();
  }
  return d;
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
