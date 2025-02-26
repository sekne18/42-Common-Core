#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "Bureaucrat.hpp"
#include "Intern.hpp"

void	sectionTitle(const std::string& title) {
	std::cout	<< std::endl
				<< "*** " << title << " ***"
				<< std::endl << std::endl;
}

Bureaucrat	burro("burro", 42);
Intern		interno;

void	testMake(const std::string& formName, const std::string& target) {
	sectionTitle(formName);

	AForm* form = interno.makeForm(formName, target);

	std::cout << *form;
	burro.signForm(*form);
	burro.executeForm(*form);

	delete form;
}

int	main() {
	try {
		testMake("robotomy request", "Bender");
		testMake("presidential pardon", "lrocca");
		testMake("shrubbery creation", "home");
		testMake("not a form", "you");
	}
	catch (std::exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
	}
}