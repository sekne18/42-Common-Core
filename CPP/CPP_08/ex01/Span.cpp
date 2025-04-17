#include "Span.hpp"

Span::Span() : _size(0)
{
}

Span::Span(unsigned int n) : _size(n)
{
}

Span::Span(const Span &copy)
{
  *this = copy;
}

Span::~Span()
{
}

Span &Span::operator=(const Span &ref)
{
  if (this != &ref)
  {
    _size = ref._size;
    _arr = ref._arr;
  }
  return *this;
}

void Span::addNumber(std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
  if (_arr.size() + std::distance(begin, end) <= _size)
    _arr.insert(_arr.end(), begin, end);
  else
    throw FullException(); 
}


void Span::addNumber(int num)
{
  if (_arr.size() < _size)
    _arr.push_back(num);
  else
    throw FullException(); 
}
 
int Span::shortestSpan()
{
  if (_arr.size() > 1)
  {
    std::sort(_arr.begin(), _arr.end());
    int shortest = INT_MAX;
    for (size_t i = 1; i < _arr.size(); i++)
    {
      if ((_arr.at(i) - _arr.at(i-1)) < shortest)
        shortest = _arr.at(i) - _arr.at(i-1);
    }
    return shortest; 
  }
  else
    throw LowAmountElemenetsException();
}

int Span::longestSpan()
{
  if (_arr.size() > 1)
    return *std::max_element(_arr.begin(), _arr.end()) - *std::min_element(_arr.begin(), _arr.end());
  else
    throw LowAmountElemenetsException(); 
}
