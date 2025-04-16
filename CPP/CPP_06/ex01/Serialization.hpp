#ifndef SERIALIZATION_HPP
#define SERIALIZATION_HPP

#include <iostream>
#include <stdint.h> 

struct Data
{
  int i;
  char c;
  float f;
  double d;
  std::string str;
};

/*
 * This does not change the actual memory, only how the program interprets it. 
*/
class Serialization
{
private:
  Serialization();
  
public:
  ~Serialization();
  static uintptr_t serialize(Data* ptr);
  static Data* deserialize(uintptr_t raw);


};

#endif // SERIALIZATION_HPP
