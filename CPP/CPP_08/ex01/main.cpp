#include "Span.hpp"

int main()
{
  Span sp = Span(5);
  sp.addNumber(6);
  sp.addNumber(3);
  sp.addNumber(17);
  sp.addNumber(9);
  sp.addNumber(11);
  std::cout << sp.shortestSpan() << std::endl;
  std::cout << sp.longestSpan() << std::endl;
  
  // Add 10000 number using addNumber() with begin and end iterators.
  {
    Span sp = Span(10000);
    std::vector<int> num;
    for (int i = 0; i < 10000; i++)
      num.push_back(rand() % 10000);
    sp.addNumber(num.begin(), num.end());
    std::cout << sp.shortestSpan() << std::endl;
    std::cout << sp.longestSpan() << std::endl;
  }
  return (0);
}
