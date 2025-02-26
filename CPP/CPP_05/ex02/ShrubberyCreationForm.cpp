#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(std::string target) : AForm("Shrubbery Creation Form", 145, 137), _target(target)
{
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm & shrubbery_creation_form) : AForm(shrubbery_creation_form)
{
    *this = shrubbery_creation_form;
}  

ShrubberyCreationForm & ShrubberyCreationForm::operator=(const ShrubberyCreationForm & shrubbery_creation_form)
{
    if (this == &shrubbery_creation_form)
        return *this;
    _target = shrubbery_creation_form._target;
    return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
}   

void ShrubberyCreationForm::execute(Bureaucrat const & executor) const
{
    AForm::execute(executor);
    std::ofstream file((_target + "_shrubbery").c_str());
    if (!file.is_open())
        throw std::runtime_error("Error: could not open file");
    file << "       _-_\n    /~~   ~~\\\n /~~         ~~\\\n{               }\n \\  _-     -_  /\n   ~  \\\\ //  ~\n_- -   | | _- _\n  _ -  | |   -_\n      // \\\n";
    file.close();
}