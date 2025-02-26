#include "Fixed.hpp"

const int Fixed::_fractionalBits = 8;

Fixed::Fixed() : _value(0)
{
  std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const Fixed &fixed)
{
  std::cout << "Copy constructor called" << std::endl;
  *this = fixed;
}

Fixed::Fixed(const int value)
{
  std::cout << "Int constructor called" << std::endl;
  _value = value << _fractionalBits;
}

Fixed::Fixed(const float value)
{
  std::cout << "Float constructor called" << std::endl;
  _value = roundf(value * (1 << _fractionalBits));
}

Fixed::~Fixed()
{
  std::cout << "Destructor called" << std::endl;
}

Fixed &Fixed::operator=(const Fixed &fixed)
{
  std::cout << "Copy assignment operator called" << std::endl;
  _value = fixed.getRawBits();
  return *this;
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
