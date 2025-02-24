#include "Bureaucrat.hpp"

int main()
{
  Form f1("f1", 100, 50);
  std::cout << "Form name: " << f1.getName() << std::endl;
  std::cout << f1.getSigned() << std::endl;

  Bureaucrat b1("b1", 150);
  std::cout << b1.getName() << std::endl;
  std::cout << b1.getGrade() << std::endl;

  try
  {
    f1.beSigned(b1);
  }
  catch (std::exception &e)
  {
    std::cout << e.what() << std::endl;
  }

  /*try {
    while (1)
    {
      b1.incrementGrade();
      std::cout << b1 << std::endl;
    }
  }
  catch (std::exception &e)
  {
    std::cout << e.what() << std::endl;
  }*/

  return 0;
}
