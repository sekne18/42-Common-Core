#ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP

#include "AForm.hpp"
#include <math.h>

class RobotomyRequestForm : public AForm
{
    private:
        std::string _target;
    public:
        RobotomyRequestForm(std::string target);
        RobotomyRequestForm(const RobotomyRequestForm &other);
        virtual ~RobotomyRequestForm();
        RobotomyRequestForm &operator=(const RobotomyRequestForm &other);
        std::string getTarget() const;
        void execute(Bureaucrat const &executor) const;
};

#endif // ROBOTOMYREQUESTFORM_HPP