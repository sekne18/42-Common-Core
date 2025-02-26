#ifndef PRESIDENTALPARDONFORM_HPP
#define PRESIDENTALPARDONFORM_HPP

#include "AForm.hpp"

class PresidentalPardonForm : public AForm
{
    private:
        std::string _target;
    public:
        PresidentalPardonForm(std::string target);
        PresidentalPardonForm(const PresidentalPardonForm & PresidentalPardonForm);
        PresidentalPardonForm & operator=(const PresidentalPardonForm & PresidentalPardonForm);
        ~PresidentalPardonForm();
        void execute(Bureaucrat const & executor) const;
};

#endif // PRESIDENTALPARDONFORM_HPP