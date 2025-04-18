#include "ScalarConverter.hpp"

char ScalarConverter::toChar(std::string const &value)
{
  char c;
  char* endptr;

  try {
    int i = std::strtol(value.c_str(), &endptr, 10);
    if (i < 32 || i > 126) {
      throw ScalarConverter::NonDisplayableException();
    }
    c = static_cast<char>(i);
    if (endptr == value.c_str()) {
      throw ScalarConverter::ImpossibleException();
    }
  } catch (std::exception &e) {
    throw ScalarConverter::ImpossibleException();
  }
  return c;
}

int ScalarConverter::toInt(std::string const &value)
{
  long i;
  char* endptr;

  try {
    i = std::strtol(value.c_str(), &endptr, 10);
    if (endptr == value.c_str() || i > INT_MAX || i < INT_MIN) {
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
  try {
    f = std::strtof(value.c_str(), NULL);
  } catch (std::exception &e) {
    throw ScalarConverter::ImpossibleException();
  }
  return f;
}

double ScalarConverter::toDouble(std::string const &value)
{
  double d;
  try {
    d = std::strtod(value.c_str(), NULL);
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
