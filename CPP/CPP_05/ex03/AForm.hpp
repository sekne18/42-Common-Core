
#ifndef FORM_HPP
#define FORM_HPP

#include <iostream>
#include "Bureaucrat.hpp"

class AForm
{
private:
  std::string _name;
  bool _signed;
  int _gradeToSign;
  int _gradeToExec;

public:
  AForm();
  AForm(const AForm &f);
  AForm(std::string name, int gradeToSign, int gradeToExec);
  AForm &operator=(const AForm &f);
  std::string getName() const;
  int getGradeToSign() const;
  int getGradeToExec() const;
  bool getSigned() const;
  virtual ~AForm();
  void beSigned(Bureaucrat &b);
  virtual void execute(Bureaucrat const &executor) const = 0;
  
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

};

std::ostream &operator<<(std::ostream &out, const AForm &f);

#endif // AFORM_HPP
