#ifndef INTERN_HPP
#define INTERN_HPP

#include "AForm.hpp"

class Intern
{
private:
    std::string _name;
    std::string _target;
public:
    Intern();
    Intern(const std::string& name);
    Intern(const Intern& intern);
    ~Intern();
    Intern& operator=(const Intern& intern);

    AForm* makeForm(const std::string& formName, const std::string& target);
    AForm* createShrubberyCreationForm(const std::string& target);
    AForm* createRobotomyRequestForm(const std::string& target);
    AForm* createPresidentialPardonForm(const std::string& target);
    class FormNotFoundException : public std::exception {
        virtual const char* what() const throw();
    };
};

#endif // INTERN_HPP