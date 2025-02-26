#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm(std::string target) : AForm("Robotomy Request Form", 72, 45), _target(target)
{
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &other) : AForm(other)
{
}   

RobotomyRequestForm::~RobotomyRequestForm()
{
}

RobotomyRequestForm &RobotomyRequestForm::operator=(const RobotomyRequestForm &other)
{
    AForm::operator=(other);
    return (*this);
}

std::string RobotomyRequestForm::getTarget() const
{
    return (_target);
}

void RobotomyRequestForm::execute(Bureaucrat const &executor) const
{
    AForm::execute(executor);
    std::cout << "*drilling noises*" << std::endl;
    if (rand() % 2)
        std::cout << this->getTarget() << " has been robotomized successfully" << std::endl;
    else
        std::cout << this->getTarget() << " robotomization failed" << std::endl;
}