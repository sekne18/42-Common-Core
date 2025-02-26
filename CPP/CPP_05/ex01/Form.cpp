#include "Form.hpp"

Form::Form() : _name("default"), _signed(false), _gradeToSign(150), _gradeToExec(150)
{
}

Form::Form(const Form &f) : _name(f._name), _signed(f._signed), _gradeToSign(f._gradeToSign), _gradeToExec(f._gradeToExec)
{
}

Form::Form(std::string name, int gradeToSign, int gradeToExec) : _name(name), _signed(false), _gradeToSign(gradeToSign), _gradeToExec(gradeToExec)
{
}

Form &Form::operator=(const Form &f)
{
  _signed = f._signed;
  return *this;
}

Form::~Form()
{
}

std::string Form::getName() const
{
  return _name;
}

bool Form::getSigned() const
{
  return _signed;
}

void Form::beSigned(Bureaucrat &b)
{
  if (b.getGrade() <= _gradeToSign)
    _signed = true;
  else
    throw Form::GradeTooLowException();
}

int Form::getGradeToSign() const
{
  return _gradeToSign;
}

int Form::getGradeToExec() const
{
  return _gradeToExec;
}

std::ostream &operator<<(std::ostream &out, const Form &f)
{
  out << "Form " << f.getName() << " is ";
  if (f.getSigned())
    out << "signed";
  else
    out << "not signed";
  out << " and requires grade " << f.getGradeToSign() << " to sign and grade " << f.getGradeToExec() << " to execute.";
  return out;
}

const char *Form::GradeTooLowException::what() const throw()
{
  return "Grade is too low";
}

const char *Form::GradeTooHighException::what() const throw()
{
  return "Grade is too high";
}
