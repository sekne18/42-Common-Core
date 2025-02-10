#include "Fixed.hpp"

const int Fixed::_fractionalBits = 8;

Fixed::Fixed() : _value(0)
{
  std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const Fixed &fixed)
{
  *this = fixed;
}

Fixed::Fixed(const int value)
{
  _value = value << _fractionalBits;
}

Fixed::Fixed(const float value)
{
  _value = roundf(value * (1 << _fractionalBits));
}

Fixed::~Fixed()
{
}

/*
 * [ OPERATORS ]
 */
Fixed &Fixed::operator=(const Fixed &fixed)
{
  _value = fixed.getRawBits();
  return *this;
}

/*
 * [ ARITHMETIC OPERATORS ]
 * */
Fixed Fixed::operator+(const Fixed &fixed) const
{
  return Fixed(toFloat() + fixed.toFloat());
}

Fixed Fixed::operator-(const Fixed &fixed) const
{
  return Fixed(toFloat() - fixed.toFloat());
}

Fixed Fixed::operator*(const Fixed &fixed) const
{
  return Fixed(toFloat() * fixed.toFloat());
}

Fixed Fixed::operator/(const Fixed &fixed) const
{
  return Fixed(toFloat() / fixed.toFloat());
}

/*
 * [ LOGICAL OPERATORS ]
 * */
bool Fixed::operator>(const Fixed &fixed) const
{
  return _value > fixed.getRawBits();
}

bool Fixed::operator<(const Fixed &fixed) const
{
  return _value < fixed.getRawBits();
}

bool Fixed::operator>=(const Fixed &fixed) const
{
  return _value >= fixed.getRawBits();
}

bool Fixed::operator<=(const Fixed &fixed) const
{
  return _value <= fixed.getRawBits();
}

bool Fixed::operator==(const Fixed &fixed) const
{
  return _value == fixed.getRawBits();
}

bool Fixed::operator!=(const Fixed &fixed) const
{
  return _value != fixed.getRawBits();
}

/*
 * [ INCREMENT & DECREMENT OPERATORS ]
 * */
Fixed &Fixed::operator++()
{
  _value++;
  return *this;
}

Fixed Fixed::operator++(int)
{
  Fixed tmp(*this);
  operator++();
  return tmp;
}

Fixed &Fixed::operator--()
{
  _value--;
  return *this;
}

Fixed Fixed::operator--(int)
{
  Fixed tmp(*this);
  operator--();
  return tmp;
}

/*
 * [ MATH FUNCTIONS ]
 * */
Fixed &Fixed::min(Fixed &a, Fixed &b)
{
  return a < b ? a : b;
}

const Fixed &Fixed::min(const Fixed &a, const Fixed &b)
{
  return a < b ? a : b;
}

Fixed &Fixed::max(Fixed &a, Fixed &b)
{
  return a > b ? a : b;
}

const Fixed &Fixed::max(const Fixed &a, const Fixed &b)
{
  return a > b ? a : b;
}

int Fixed::getRawBits(void) const
{
  return _value;
}

std::ostream &operator<<(std::ostream &out, Fixed const &value)
{
  out << value.toFloat();
  return out;
}

void Fixed::setRawBits(int const raw)
{
  _value = raw;
}

float Fixed::toFloat(void) const
{
  return (float)_value / (1 << _fractionalBits);
}

int Fixed::toInt(void) const
{
  return _value >> _fractionalBits;
}
