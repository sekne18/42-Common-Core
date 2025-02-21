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
