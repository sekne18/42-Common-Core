#include "Bureaucrat.hpp"
#include "Form.hpp"

int main()
{
  Form f1("f1", 40, 50);
  Bureaucrat b1("b1", 60);
  

  try
  {
    b1.signForm(f1);
    std::cout << f1 << std::endl;
  }
  catch (std::exception &e)
  {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
