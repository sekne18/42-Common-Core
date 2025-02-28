#ifndef WRONGANIMAL_CPP
#define WRONGANIMAL_CPP

#include <iostream>

class WrongAnimal
{
protected:
  std::string _type;
  std::string _sound;

public:
    WrongAnimal();
    WrongAnimal(const WrongAnimal &other);
    WrongAnimal &operator=(const WrongAnimal &other);
    ~WrongAnimal();
    void makeSound() const;
    std::string getType() const;
};

#endif // WRONGANIMAL_CPP
