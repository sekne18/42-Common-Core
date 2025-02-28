#include "ICharacter.hpp"

ICharacter::ICharacter() {}

ICharacter::ICharacter(const ICharacter &copy) {
  *this = copy;
}

ICharacter &ICharacter::operator=(const ICharacter &copy) {
  (void)copy;
  return *this;
}

ICharacter::~ICharacter() {}

std::string const &ICharacter::getName() const {
  return this->_name;
}

void ICharacter::equip(AMateria *m) {
  if (m == NULL)
    return;
  for (int i = 0; i < 4; i++) {
    if (this->_inventory[i] == NULL) {
      this->_inventory[i] = m;
      break;
    }
  }
}

void ICharacter::unequip(int idx) {
  if (idx < 0 || idx > 3 || this->_inventory[idx] == NULL)
    return;
  this->_inventory[idx] = NULL;
}

void ICharacter::use(int idx, ICharacter &target) {
  if (idx < 0 || idx > 3 || this->_inventory[idx] == NULL)
    return;
  this->_inventory[idx]->use(target);
}

AMateria *ICharacter::getMateriaFromInventory(int idx) {
  if (idx < 0 || idx > 3)
    return NULL;
  return this->_inventory[idx];
}

void ICharacter::setName(std::string name) {
  this->_name = name;
}

void ICharacter::setInventory(AMateria **inventory) {
  for (int i = 0; i < 4; i++) {
    this->_inventory[i] = inventory[i];
  }
}

AMateria **ICharacter::getInventory() {
  return this->_inventory;
}
