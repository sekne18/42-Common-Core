#include "Serialization.hpp"

int main()
{
  Data data;
  data.i = 42;
  data.c = 'a';
  data.f = 3.14f;
  data.d = 2.71828;
  data.str = "Hello, World!";
  std::cout << "Original Data:" << std::endl;
  std::cout << "i: " << data.i << std::endl;
  std::cout << "c: " << data.c << std::endl;
  std::cout << "f: " << data.f << std::endl;
  std::cout << "d: " << data.d << std::endl;
  std::cout << "str: " << data.str << std::endl;
  uintptr_t raw = Serialization::serialize(&data);
  Data* deserializedData = Serialization::deserialize(raw);
  std::cout << "\nDeserialized Data:" << std::endl;
  std::cout << "i: " << deserializedData->i << std::endl;
  std::cout << "c: " << deserializedData->c << std::endl;
  std::cout << "f: " << deserializedData->f << std::endl;
  std::cout << "d: " << deserializedData->d << std::endl;
  std::cout << "str: " << deserializedData->str << std::endl;
  return 0;
}
