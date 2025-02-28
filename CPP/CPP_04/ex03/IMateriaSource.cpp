#include "IMateriaSource.hpp"

IMateriaSource::IMateriaSource() {}

IMateriaSource::IMateriaSource(IMateriaSource const & src)
{
  *this = src;
}

IMateriaSource & IMateriaSource::operator=(IMateriaSource const & src)
{
  (void)src;
  return *this;
}

IMateriaSource::~IMateriaSource() {}

void IMateriaSource::learnMateria(AMateria *m)
{
  (void)m;
}

AMateria *IMateriaSource::createMateria(std::string const &type)
{
  (void)type;
  return NULL;
}
