#ifndef CAT_HPP
#define CAT_HPP

#include "Animal.hpp"
#include "Brain.hpp"

class Cat : public AAnimal
{
private:
  Brain *_brain;

public:
  Cat();
  ~Cat();
  virtual void makeSound() const;

};


#endif // CAT_HPP
