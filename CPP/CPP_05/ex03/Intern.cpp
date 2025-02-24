#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

Intern::Intern() : _name("default"), _target("default") {}

Intern::Intern(const std::string& name) : _name(name), _target("default") {}

Intern::Intern(const Intern& intern) : _name(intern._name), _target(intern._target) {}

Intern::~Intern() {}

Intern& Intern::operator=(const Intern& intern) {
    if (this == &intern)
        return *this;
    _name = intern._name;
    _target = intern._target;
    return *this;
}

AForm* Intern::makeForm(const std::string& formName, const std::string& target) {
    if (formName == "shrubbery creation")
        return createShrubberyCreationForm(target);
    if (formName == "robotomy request")
        return createRobotomyRequestForm(target);
    if (formName == "presidential pardon")
        return createPresidentialPardonForm(target);
    throw Intern::FormNotFoundException();
}

AForm* Intern::createShrubberyCreationForm(const std::string& target) {
    return new ShrubberyCreationForm(target);
}

AForm* Intern::createRobotomyRequestForm(const std::string& target) {
    return new RobotomyRequestForm(target);
}

AForm* Intern::createPresidentialPardonForm(const std::string& target) {
    return new PresidentialPardonForm(target);
}

const char* Intern::FormNotFoundException::what() const throw() {
    return "Form not found";
}
