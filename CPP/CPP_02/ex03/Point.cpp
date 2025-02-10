
#include "Point.hpp"

Point::Point() : x(Fixed(0)), y(Fixed(0)) {}

Point::Point(const Fixed &x, const Fixed &y) : x(x), y(y) {}

Point::Point(const Point& p) : x(p.x), y(p.y) {}

Point &Point::operator=(const Point &p)
{
  (void)p;
  return *this;
}

Point::~Point() {}

Fixed Point::getX() const
{
  return x;
}

Fixed Point::getY() const
{
  return y;
}
