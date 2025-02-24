#include "AForm.hpp"

AForm::AForm() : _name("default"), _signed(false), _gradeToSign(150), _gradeToExec(150)
{
}

AForm::AForm(std::string name, int gradeToSign, int gradeToExec) : _name(name), _signed(false), _gradeToSign(gradeToSign), _gradeToExec(gradeToExec)
{
  if (gradeToSign < 1 || gradeToExec < 1)
    throw AForm::GradeTooHighException();
  if (gradeToSign > 150 || gradeToExec > 150)
    throw AForm::GradeTooLowException();
}

void AForm::execute(Bureaucrat const &executor) const
{
  if (executor.getGrade() > _gradeToExec)
    throw AForm::GradeTooLowException();
  // if (!_signed)
  //   throw AForm::FormNotSignedException();
}

AForm::AForm(const AForm &f) : _name(f._name), _signed(f._signed), _gradeToSign(f._gradeToSign), _gradeToExec(f._gradeToExec)
{
}

AForm &AForm::operator=(const AForm &f)
{
  _signed = f._signed;
  return *this;
}

AForm::~AForm()
{
}

std::string AForm::getName() const
{
  return _name;
}

bool AForm::getSigned() const
{
  return _signed;
}

void AForm::beSigned(Bureaucrat &b)
{
  if (b.getGrade() <= _gradeToSign)
    _signed = true;
  else
    throw AForm::GradeTooLowException();
}

int AForm::getGradeToSign() const
{
  return _gradeToSign;
}

int AForm::getGradeToExec() const
{
  return _gradeToExec;
}

std::ostream &operator<<(std::ostream &out, const AForm &f)
{
  out << "Form " << f.getName() << " is ";
  if (f.getSigned())
    out << "signed";
  else
    out << "not signed";
  out << " and requires grade " << f.getGradeToSign() << " to sign and grade " << f.getGradeToExec() << " to execute." << std::endl;
  return out;
}

const char *AForm::GradeTooLowException::what() const throw()
{
  return "Grade is too low";
}

const char *AForm::GradeTooHighException::what() const throw()
{
  return "Grade is too high";
}
