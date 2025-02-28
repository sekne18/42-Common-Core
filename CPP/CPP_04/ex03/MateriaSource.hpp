#ifndef MATERIASOURCE_HPP
#define MATERIASOURCE_HPP

#include <iostream>
#include "AMateria.hpp"
#include "IMateriaSource.hpp"

class AMateria;

class MateriaSource : public IMateriaSource
{
private:
  AMateria* _source[4];
public:
  MateriaSource();
  MateriaSource(MateriaSource const &src);
  MateriaSource &operator=(MateriaSource const &src);
  ~MateriaSource();
  void learnMateria(AMateria* m);
  AMateria* createMateria(std::string const &type);
  void setSource(AMateria **source);
  AMateria **getSource();
  AMateria *getMateriaFromSource(int idx);
};

#endif // MATERIASOURCE_HPP
