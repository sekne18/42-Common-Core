#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(std::string const &value) : _value(value) {}

ScalarConverter::ScalarConverter(ScalarConverter const &src) {
  *this = src;
}

ScalarConverter::~ScalarConverter() {}

ScalarConverter &ScalarConverter::operator=(ScalarConverter const &rhs) {
  if (this != &rhs) {
    _value = rhs._value;
  }
  return *this;
}

char ScalarConverter::toChar() const {
  char c;
  try {
    c = std::stoi(_value);
  } catch (std::exception &e) {
    throw ScalarConverter::ImpossibleException();
  }
  if (c < 32 || c > 126) {
    throw ScalarConverter::NonDisplayableException();
  }
  return c;
}

int ScalarConverter::toInt() const {
  int i;
  try {
    i = std::stoi(_value);
  } catch (std::exception &e) {
    throw ScalarConverter::ImpossibleException();
  }
  return i;
}

float ScalarConverter::toFloat() const {
  float f;
  try {
    f = std::stof(_value);
  } catch (std::exception &e) {
    throw ScalarConverter::ImpossibleException();
  }
  return f;
}

double ScalarConverter::toDouble() const {
  double d;
  try {
    d = std::stod(_value);
  } catch (std::exception &e) {
    throw ScalarConverter::ImpossibleException();
  }
  return d;
}

const char *ScalarConverter::ImpossibleException::what() const throw() {
  return "impossible";
}

const char *ScalarConverter::NonDisplayableException::what() const throw() {
  return "Non displayable";
}

std::string to_string(const Point& p) {
    std::ostringstream oss;
    oss << "(" << p.x << ", " << p.y << ")";
    return oss.str();
}

static void ScalarConverter::convert()
{
  try {
    std::cout << "char: ";
    std::cout << std::to_string(toChar()) << std::endl;
  } catch (ScalarConverter::ImpossibleException &e) {
    std::cout << e.what() << std::endl;
  } catch (ScalarConverter::NonDisplayableException &e) {
    std::cout << e.what() << std::endl;
  }
  try {
    std::cout << "int: ";
    std::cout << toInt() << std::endl;
  } catch (ScalarConverter::ImpossibleException &e) {
    std::cout << e.what() << std::endl;
  }
  try {
    std::cout << "float: ";
    std::cout << std::fixed << std::setprecision(1) << toFloat() << "f" << std::endl;
  } catch (ScalarConverter::ImpossibleException &e) {
    std::cout << e.what() << std::endl;
  }
  try {
    std::cout << "double: ";
    std::cout << std::fixed << std::setprecision(1) << toDouble() << std::endl;
  } catch (ScalarConverter::ImpossibleException &e) {
    std::cout << e.what() << std::endl;
  }
}
