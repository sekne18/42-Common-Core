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
  Array();
  Array(unsigned int n);
  Array(const Array& other);
  Array& operator=(const Array& other);
  ~Array();

  unsigned int size() const;
  const T& operator[](unsigned int index) const;
  T& operator[](unsigned int index);

};

template <class t>
array<t>::array() : _data(null), _size(0)
{
}

template <class t>
array<t>::array(unsigned int n) : _data(), _size(0)
{
}

template <class T>
Array<T>::~Array()
{
	delete[] _arr;
}


#endif // ARRAY_HPP
