#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

#include <iostream>
#include "Form.hpp"

class Bureaucrat
{
private:
  std::string const _name;
  int _grade;

public:
  Bureaucrat();
  Bureaucrat(std::string const name, int grade);
  Bureaucrat(Bureaucrat const &src);
  ~Bureaucrat();
  Bureaucrat &operator=(Bureaucrat const &rhs);
  std::string getName() const;
  int getGrade() const;
  void incrementGrade();
  void decrementGrade();
  void signForm(Form &form);

};

std::ostream &operator<<(std::ostream &os, const Bureaucrat &b);

class GradeTooHighException : public std::exception
{
public:
  virtual const char *what() const throw();
};

class GradeTooLowException : public std::exception
{
public:
  virtual const char *what() const throw();
};


#endif
