#include "PresidentialPardonForm.hpp"

PresidentalPardonForm::PresidentalPardonForm(std::string target) : AForm("Presidential Pardon Form", 25, 5), _target(target)
{
}

PresidentalPardonForm::PresidentalPardonForm(const PresidentalPardonForm & PresidentalPardonForm) : AForm(PresidentalPardonForm)
{
    *this = PresidentalPardonForm;
}

PresidentalPardonForm & PresidentalPardonForm::operator=(const PresidentalPardonForm & PresidentalPardonForm)
{
    if (this == &PresidentalPardonForm)
        return *this;
    _target = PresidentalPardonForm._target;
    return *this;
}

PresidentalPardonForm::~PresidentalPardonForm()
{
}

void PresidentalPardonForm::execute(Bureaucrat const & executor) const
{
    AForm::execute(executor);
    std::cout << _target << " has been pardoned by Zafod Beeblebrox" << std::endl;
}

