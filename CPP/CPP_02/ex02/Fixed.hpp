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

  Fixed operator+(const Fixed &fixed) const;
  Fixed operator-(const Fixed &fixed) const;
  Fixed operator*(const Fixed &fixed) const;
  Fixed operator/(const Fixed &fixed) const;

  Fixed &operator++(); // Pre-increment
  Fixed operator++(int); // Post-increment
  Fixed &operator--(); // Pre-decrement
  Fixed operator--(int); // Post-decrement
  
  bool operator>(const Fixed &fixed) const;
  bool operator<(const Fixed &fixed) const;
  bool operator>=(const Fixed &fixed) const;
  bool operator<=(const Fixed &fixed) const;
  bool operator==(const Fixed &fixed) const;
  bool operator!=(const Fixed &fixed) const;
  
  static Fixed &min(Fixed &a, Fixed &b);
  static const Fixed &min(const Fixed &a, const Fixed &b);
  static Fixed &max(Fixed &a, Fixed &b);
  static const Fixed &max(const Fixed &a, const Fixed &b);
  
  /* "friend" allows a non-member function to access private or protected members.
   * Can be defined outside the class 
   */
  friend std::ostream &operator<<(std::ostream &out, const Fixed &value);

};


#endif //FIXED_HPP
