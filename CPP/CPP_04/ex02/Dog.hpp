#ifndef DOG_HPP
#define DOG_HPP

#include "Animal.hpp"
#include "Brain.hpp"

class Dog : public AAnimal
{
private:
  Brain *_brain;

public:
  Dog();
  ~Dog();
  virtual void makeSound() const;

};


#endif // DOG_HPP
