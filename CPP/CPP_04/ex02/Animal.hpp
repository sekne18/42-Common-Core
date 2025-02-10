#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <iostream>

class AAnimal
{
protected:
  AAnimal();
  std::string _type;
  std::string _sound;

public:
  virtual ~AAnimal();
  virtual void makeSound() const = 0;
  std::string getType() const;

};

#endif
