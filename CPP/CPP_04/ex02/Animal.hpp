#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <iostream>

class AAnimal
{
protected:
  AAnimal();
  AAnimal(AAnimal const &src);
  std::string _type;
  std::string _sound;

public:
  AAnimal &operator=(AAnimal const &rhs);
  virtual ~AAnimal();
  virtual void makeSound() const = 0;
  std::string getType() const;

};

#endif
