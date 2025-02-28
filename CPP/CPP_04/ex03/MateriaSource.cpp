#include "MateriaSource.hpp"

MateriaSource::MateriaSource()
{
  std::cout << "MateriaSource constructor" << std::endl;
  for (int i = 0; i < 4; i++)
    _source[i] = NULL;
}

MateriaSource::MateriaSource(MateriaSource const &src)
{
  std::cout << "MateriaSource copy constructor" << std::endl;
  *this = src;
}

MateriaSource::~MateriaSource()
{
  for (int i = 0; i < 4; i++)
    if (_source[i])
      delete _source[i];
}

MateriaSource &MateriaSource::operator=(MateriaSource const &src)
{
  if (this == &src)
    return *this;
  for (int i = 0; i < 4; i++)
    _source[i] = src._source[i];
  return *this;
}

void MateriaSource::learnMateria(AMateria* m)
{
  std::cout << "Learning " << m->getType() << std::endl;
  for (int i = 0; i < 4; i++)
    if (!_source[i])
    {
      _source[i] = m;
      break;
    }
}

AMateria* MateriaSource::createMateria(std::string const &type)
{
  for (int i = 0; i < 4; i++)
    if (_source[i] && _source[i]->getType() == type)
      return _source[i]->clone();
  return NULL;
}

void MateriaSource::setSource(AMateria **source)
{
  for (int i = 0; i < 4; i++)
    _source[i] = source[i];
}

AMateria **MateriaSource::getSource()
{
  return _source;
}

AMateria *MateriaSource::getMateriaFromSource(int idx)
{
  if (idx >= 0 && idx < 4)
    return _source[idx];
  return NULL;
}
