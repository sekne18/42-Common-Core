#include "Bureaucrat.hpp"

int main()
{
  Bureaucrat b1("b1", 1);
  std::cout << b1.getName() << std::endl;
  std::cout << b1.getGrade() << std::endl;
// use try catch and call incrementGrade() and decrementGrade() to test the exceptions
  try {
    while (1)
    {
      b1.decrementGrade();
      std::cout << b1.getGrade() << std::endl;
    }
  }
  catch (GradeTooHighException &e)
  {
    std::cout << e.what() << std::endl;
  }
  catch (GradeTooLowException &e)
  {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
