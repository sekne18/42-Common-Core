#include "Bureaucrat.hpp"

int main()
{
  Bureaucrat b1("b1", 150);
  std::cout << b1.getName() << std::endl;
  std::cout << b1.getGrade() << std::endl;
  try {
    while (1)
    {
      b1.incrementGrade();
      std::cout << b1 << std::endl;
    }
  }
  catch (std::exception &e)
  {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
