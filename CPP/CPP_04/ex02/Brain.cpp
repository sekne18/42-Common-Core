#include "Brain.hpp"

Brain::Brain()
{
  std::cout << "Brain constructor called" << std::endl;
  for (int i = 0; i < 100; i++)
  {
    ideas[i] = "Ideas, ideas...";
  }
}

Brain::Brain(Brain const &src)
{
  std::cout << "Brain copy constructor called" << std::endl;
  for (int i = 0; i < 100; i++)
  {
    ideas[i] = src.getIdea(i);
  }
}

Brain &Brain::operator=(Brain const &rhs)
{
  std::cout << "Brain assignation operator called" << std::endl;
  if (this != &rhs)
  {
    for (int i = 0; i < 100; i++)
    {
      ideas[i] = rhs.getIdea(i);
    }
  }
  return *this;
}

Brain::~Brain()
{
  std::cout << "Brain destructor called" << std::endl;
}

void Brain::setIdea(int index, std::string idea)
{
  ideas[index] = idea;
}

std::string Brain::getIdea(int index) const
{
  return ideas[index];
}
