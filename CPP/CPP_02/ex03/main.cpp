#include "Point.hpp"

int main()
{
  const Point p1(Fixed(0), Fixed(0));
  const Point p2(Fixed(0), Fixed(4));
  const Point p3(Fixed(4), Fixed(0));
  const Point pointInside(Fixed(1), Fixed(1));
  const Point pointOutside(Fixed(5), Fixed(5));
  bool res1 = bsp(p1, p2, p3, pointInside);
  bool res2 = bsp(p1, p2, p3, pointOutside);

  if (res1)
    std::cout << "Point " << pointInside.getX() << ", " << pointInside.getY() << " inside triangle: " << "true" << std::endl;
  else
    std::cout << "Point " << pointInside.getX() << ", " << pointInside.getY() << " inside triangle: " << "true" << std::endl;
  
  if (res2)
    std::cout << "Point "  << pointOutside.getX() << ", " << pointOutside.getY() <<  " inside triangle: " << "false" << std::endl;
  else
    std::cout << "Point "  << pointOutside.getX() << ", " << pointOutside.getY() <<  " inside triangle: " << "false" << std::endl;
  return 0;  
}
