#include "easyfind.hpp"

int main()
{
  std::vector<int> arr;
  int size = 10;

  for (int i = 0; i < size; i++)
    arr.push_back(i);

  try {
    std::cout << "Value: " << *easyfind(arr, 9) << " was found!" << std::endl;
  }
  catch (const std::exception &e) {
    std::cout << e.what() << std::endl;
  }
  
  return (0);
}
