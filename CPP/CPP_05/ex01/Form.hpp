
#ifndef FORM_HPP
#define FORM_HPP

#include <iostream>
#include "Bureaucrat.hpp"

class Form
{
private:
  std::string _name;
  bool _signed;
  int _gradeToSign;
  int _gradeToExec;

public:
  Form();
  Form(const Form &f);
  Form(std::string name, int gradeToSign, int gradeToExec);
  Form &operator=(const Form &f);
  std::string getName() const;
  int getGradeToSign() const;
  int getGradeToExec() const;
  bool getSigned() const;
  virtual ~Form();
  void beSigned(Bureaucrat &b);
  
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

std::ostream &operator<<(std::ostream &out, const Form &f);

#endif // FORM_HPP
