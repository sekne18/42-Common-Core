#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "Bureaucrat.hpp"

void	testForm(Bureaucrat& bureaucrat, AForm& form) {
	std::cout << form;
	bureaucrat.signForm(form);
	bureaucrat.executeForm(form);
}

int main()
{
  Bureaucrat	burro("burro", 1);
	Bureaucrat	burretto("burretto", 42);
	std::cout << burro << burretto << std::endl;

	try {
		{
			std::cout << "shrubbery creation" << std::endl;
			ShrubberyCreationForm form("home");
			testForm(burro, form);
		}
		{
			std::cout << "robotomy request" << std::endl;
			RobotomyRequestForm form("Bender");
			testForm(burro, form);
		}
		{
			std::cout << "presidential pardon" << std::endl;
			PresidentalPardonForm form("lrocca");
			testForm(burro, form);
		}
		PresidentalPardonForm form("lrocca");
		{
			std::cout << "execute unsigned form" << std::endl;
			std::cout << form;
			burro.executeForm(form);
		}
		{
			std::cout << "too low to execute" << std::endl;
			burro.signForm(form);
			burretto.executeForm(form);
		}
	}
	catch (std::exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
	}
  return 0;
}
