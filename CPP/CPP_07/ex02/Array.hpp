#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iostream>
#include <cstdlib>

template <typename T>
class Array
{
private:
  T* _data;
  unsigned int _size;

public:
  Array() : _data(NULL), _size(0) {}

  Array(unsigned int n) : _size(n) {
    if (n == 0)
      _data = NULL;
    else
      _data = new T[n];
  }

  ~Array()
  {
	  delete[] _data;
  }

  Array(const Array& other) : _data(), _size(0)
  {
    *this = other;
  }

  Array<T>& operator=(const Array& other)
  {
    if (this != &other)
    {
      delete[] _data;
      _size = other._size;
      _data = new T[_size];
      for (unsigned int i = 0; i < _size; ++i)
        _data[i] = other._data[i];
    }
    return *this;
  }

  unsigned int size() const
  {
    return _size;
  }

  const T& operator[](unsigned int index) const
  {
    if (index >= _size)
      throw std::out_of_range("Index out of range");
    return _data[index];
  }

  T& operator[](unsigned int index)
  {
    if (index >= _size)
      throw std::out_of_range("Index out of range");
    return _data[index];
  }
};

#endif // ARRAY_HPP
