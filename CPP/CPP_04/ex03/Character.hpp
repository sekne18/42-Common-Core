#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <iostream>
#include "ICharacter.hpp"

class AMateria;

class Character : public ICharacter
{
private:
  std::string const _name;
  AMateria* _inventory[4];
public:
  Character(std::string const &name = "default");
  Character(Character const &src);
  ~Character();

  Character &operator=(Character const &src);

  std::string const &getName() const;
  void equip(AMateria* m);
  void unequip(int idx);
  void use(int idx, ICharacter& target);
  AMateria *getMateriaFromInventory(int idx);
};

#endif // CHARACTER_HPP
