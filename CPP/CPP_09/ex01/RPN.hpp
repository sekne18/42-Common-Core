#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <stdlib.h>

class RPN
{
private:
  std::stack<int> _stack;
  class ErrorException : public std::exception {
  public:
    const char *what() const throw();
  };

public:
  RPN();
  ~RPN();
  RPN(const RPN &other);
  RPN &operator=(const RPN &other);
  void processInput(const std::string &input);

};

#endif // RPN_HPP
