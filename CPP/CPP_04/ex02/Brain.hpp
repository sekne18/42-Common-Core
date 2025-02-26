#ifndef BRAIN_HPP
#define BRAIN_HPP

#include <iostream>

class Brain
{
private:
  std::string ideas[100];

public:
  Brain();
  Brain(Brain const &src);
  Brain &operator=(Brain const &rhs);
  ~Brain();
  void setIdea(int index, std::string idea);
  std::string getIdea(int index) const;
};

#endif // BRAIN_HPP
