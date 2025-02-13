#ifndef DOG_HPP
#define DOG_HPP

#include "Animal.hpp"
#include "Brain.hpp"

class Dog : public Animal
{
private:
  Brain *_brain;

public:
  Dog();
  ~Dog();
  void makeSound() const;

};


#endif // DOG_HPP
