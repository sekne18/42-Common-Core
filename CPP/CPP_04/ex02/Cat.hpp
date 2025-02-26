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
  Cat(Cat const &src);
  Cat &operator=(Cat const &rhs);
  ~Cat();
  void makeSound() const;

};

#endif // CAT_HPP
