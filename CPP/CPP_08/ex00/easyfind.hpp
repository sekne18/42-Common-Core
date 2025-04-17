#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <iostream>
#include <algorithm>
#include <vector>


class NotFoundException: public std::exception
{
	public:
			virtual const char *what() const throw()
			{
				return ("Not found");
			}
};

template <typename T>
typename T::iterator easyfind(T &list, int toFind)
{
  typename T::iterator it = find(list.begin(), list.end(), toFind);
  if (it != list.end())
    return it;
  else
    throw NotFoundException();
}

#endif // EASYFIND_HPP
