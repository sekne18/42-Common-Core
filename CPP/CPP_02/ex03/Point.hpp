#ifndef  POINT_HPP
#define  POINT_HPP

#include <iostream>
#include <cmath>
#include "Fixed.hpp"

class Point 
{
private:
  Fixed const x;
  Fixed const y;

public:
  Point();
  Point(const Fixed &x, const Fixed &y);
  Point(const Point& p);
  ~Point();

  Point &operator=(const Point &p);
  
  Fixed getX() const;
  Fixed getY() const;
};

bool bsp( Point const a, Point const b, Point const c, Point const point);

#endif   // POINT_HPP
