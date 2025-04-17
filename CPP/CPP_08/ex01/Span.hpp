#ifndef SPAN_HPP
#define SPAN_HPP

#include <iostream>
#include <algorithm>
#include <vector>
#include <limits.h>

class Span
{
private:
  unsigned int _size;
  std::vector<int> _arr;

public:
  Span();
  Span(unsigned int n);
  Span(const Span &copy);
  ~Span();

  Span &operator=(const Span &ref);

  void addNumber(int num);
  void addNumber(std::vector<int>::iterator begin, std::vector<int>::iterator end);
  int shortestSpan();
  int longestSpan();

  class FullException: public std::exception
  {
	public:
		virtual const char *what() const throw()
		{
			return ("Container is full");
		}
  };

  class LowAmountElemenetsException: public std::exception
  {
	public:
		virtual const char *what() const throw()
		{
			return ("There are not enough elements");
		}
  };
};

#endif // SPAN_HPP
