#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(std::string target) : AForm("Presidential Pardon Form", 25, 5), _target(target)
{
}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm & PresidentialPardonForm) : AForm(PresidentialPardonForm)
{
    *this = PresidentialPardonForm;
}

PresidentialPardonForm & PresidentialPardonForm::operator=(const PresidentialPardonForm & PresidentialPardonForm)
{
    if (this == &PresidentialPardonForm)
        return *this;
    _target = PresidentialPardonForm._target;
    return *this;
}

PresidentialPardonForm::~PresidentialPardonForm()
{
}

void PresidentialPardonForm::execute(Bureaucrat const & executor) const
{
    AForm::execute(executor);
    std::cout << _target << " has been pardoned by Zafod Beeblebrox" << std::endl;
}

