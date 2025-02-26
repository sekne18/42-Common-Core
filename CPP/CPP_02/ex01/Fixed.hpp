#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
#include <cmath>

class Fixed
{
private:
  int _value;
  static const int _fractionalBits;
public:
  Fixed(); // Constructor
  Fixed(const Fixed &fixed); // Copy Constructor
  ~Fixed(); // Destructor
  Fixed(const int value);
  Fixed(const float value);
  Fixed &operator=(const Fixed &fixed);
  int getRawBits(void) const;
  void setRawBits(int const raw);
  float toFloat(void) const;
  int toInt(void) const;

};

std::ostream &operator<<(std::ostream &out, const Fixed &value);

#endif //FIXED_HPP
