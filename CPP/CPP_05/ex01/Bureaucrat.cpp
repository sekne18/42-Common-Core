#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat() : _name("default"), _grade(150)
{ 
}

Bureaucrat::Bureaucrat(std::string const name, int grade) : _name(name), _grade(grade)
{
  if (grade < 1)
    throw GradeTooHighException();
  if (grade > 150)
    throw GradeTooLowException();
}

Bureaucrat::Bureaucrat(Bureaucrat const &src) : _name(src._name), _grade(src._grade)
{
}

Bureaucrat::~Bureaucrat()
{
}

void Bureaucrat::signForm(Form &form)
{
  try
  {
    form.beSigned(*this);
    std::cout << _name << " signed " << form.getName() << std::endl;
  }
  catch (std::exception &e)
  {
    std::cout << _name << " couldn't sign " << form.getName() << " because " << e.what() << std::endl;
  }
}

std::ostream &operator<<(std::ostream &o, Bureaucrat const &rhs)
{
  o << rhs.getName() << ", bureaucrat grade " << rhs.getGrade() << std::endl;
  return o;
}

Bureaucrat &Bureaucrat::operator=(Bureaucrat const &rhs)
{
  if (this != &rhs)
  {
    _grade = rhs._grade;
  }
  return *this;
}

std::string Bureaucrat::getName() const
{
  return _name;
}

int Bureaucrat::getGrade() const
{
  return _grade;
}

const char *GradeTooHighException::what() const throw()
{
  return "Grade is too high";
}

const char *GradeTooLowException::what() const throw()
{
  return "Grade is too low";
}

void Bureaucrat::decrementGrade()
{
  if (_grade == 150)
    throw GradeTooLowException();
  _grade++;
}

void Bureaucrat::incrementGrade()
{
  if (_grade == 1)
    throw GradeTooHighException();
  _grade--;
}
