#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <iostream>

class Animal
{
protected:
  std::string _type;
  std::string _sound;

public:
  Animal();
  virtual ~Animal();
  Animal(const Animal &other);
  Animal &operator=(const Animal &other);
  virtual void makeSound() const;
  std::string getType() const;

};

#endif
