#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

class Fixed
{
private:
  int _value;
  static const int _fractionalBits;
public:
  Fixed(); // Constructor
  Fixed(const Fixed &fixed); // Copy Constructor
  ~Fixed(); // Destructor
  Fixed &operator=(const Fixed &fixed);
  int getRawBits(void) const;
  void setRawBits(int const raw);

};


#endif //FIXED_HPP
