#include "Character.hpp"

Character::Character(std::string const &name) : _name(name)
{
  std::cout << "Character " << _name << " created" << "\n";
  for (int i = 0; i < 4; i++)
    this->_inventory[i] = NULL;
}

Character::Character(Character const &src) : _name(src._name + "_copy")
{
  std::cout << "Character " << src._name << " copied" << "\n";
  for (int i = 0; i < 4; i++)
  {
    if (src._inventory[i])
      this->_inventory[i] = (src._inventory[i])->clone();
    else
      this->_inventory[i] = NULL;
  }
  std::cout << "Character " << _name << " created from copy of " << src._name << "\n";
}

Character::~Character()
{
  for (int i = 0; i < 4; i++)
    if (this->_inventory[i])
      delete this->_inventory[i];
  std::cout << "Character " << this->_name << " destroyed" << "\n";
}

Character &Character::operator=(Character const &src)
{
  for (int i = 0; i < 4; i++)
  {
    if (this->_inventory[i])
      delete this->_inventory[i];
    if (src._inventory[i])
      this->_inventory[i] = (src._inventory[i])->clone();
  }
  return *this;
}

std::string const &Character::getName() const
{
  return _name;
}

void Character::equip(AMateria* m)
{
  if (!m)
  {
    std::cout << "Cannot equip NULL materia" << "\n";
    return;
  }
  for (int i = 0; i < 4; i++)
    if (!(this->_inventory)[i])
    {
      std::cout << "Equipping " << m->getType() << " to " << _name << "\n";
      (this->_inventory)[i] = m;
      break;
    }
}

void Character::unequip(int idx)
{
  
  if (idx >= 0 && idx < 4)
  {
    (this->_inventory)[idx] = NULL;
    std::cout << "Unequipping slot " << idx << " from " << _name << "\n";
  }
}

void Character::use(int idx, ICharacter& target)
{
  if (idx >= 0 && idx < 4 && (this->_inventory)[idx])
  {
    std::cout << "Using " << (this->_inventory)[idx]->getType() << " on " << target.getName() << "\n";
    std::cout << this->getName();
    (this->_inventory)[idx]->use(target);
  }
}

AMateria *Character::getMateriaFromInventory(int idx)
{
  if (idx >= 0 && idx < 4)
    return (this->_inventory)[idx];
  return NULL;
}
