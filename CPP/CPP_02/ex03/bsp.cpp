
#include "Point.hpp"
/*
 * returns true if the point is on the positive side of the plane
 * */
bool bsp( Point const a, Point const b, Point const c, Point const point)
{
  float denom = ((b.getY() - c.getY()) * (a.getX() - c.getX()) + (c.getX() - b.getX()) * (a.getY() - c.getY())).toFloat();
  float alpha = (((b.getY() - c.getY()) * (point.getX() - c.getX()) + (c.getX() - b.getX()) * (point.getY() - c.getY())) / denom).toFloat();
  float beta = (((c.getY() - a.getY()) * (point.getX() - c.getX()) + (a.getX() - c.getX()) * (point.getY() - c.getY())) / denom).toFloat();
  float gamma = 1.0f - alpha - beta;

  return (alpha >= 0 && beta >= 0 && gamma >= 0) && (alpha <= 1 && beta <= 1 && gamma <= 1);
}
