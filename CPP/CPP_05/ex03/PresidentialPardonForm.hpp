#ifndef PRESIDENTALPARDONFORM_HPP
#define PRESIDENTALPARDONFORM_HPP

#include "AForm.hpp"

class PresidentialPardonForm : public AForm
{
    private:
        std::string _target;
    public:
        PresidentialPardonForm(std::string target);
        PresidentialPardonForm(const PresidentialPardonForm & PresidentialPardonForm);
        PresidentialPardonForm & operator=(const PresidentialPardonForm & PresidentialPardonForm);
        ~PresidentialPardonForm();
        void execute(Bureaucrat const & executor) const;
};

#endif // PRESIDENTALPARDONFORM_HPP