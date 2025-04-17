#include "Array.hpp"

#define MAX_VAL 10
int main()
{
  Array<int> numbers(MAX_VAL);
  int* mirror = new int[MAX_VAL];
  srand(time(NULL));
  for (int i = 0; i < MAX_VAL; i++)
  {
    const int value = rand() % 100;
    numbers[i] = value;
    mirror[i] = value;
  }

  //SCOPE
  {
    Array<int> tmp = numbers;
    Array<int> test(tmp);
  }
  
  // Print out the values from numbers and mirror
  {
    std::cout << "Mirror and Numbers values:" << std::endl;
    for (int i = 0; i < MAX_VAL; i++)
      std::cout << mirror[i] << " ";
    std::cout << std::endl;
    for (int i = 0; i < MAX_VAL; i++)
      std::cout << numbers[i] << " ";
    std::cout << std::endl;
  }

  // Compare the values from numbers and mirror
  for (int i = 0; i < MAX_VAL; i++)
  {
    if (mirror[i] != numbers[i])
    {
      std::cerr << "didn't save the same value!!" << std::endl;
      return 1;
    }
  }

  try
  {
    std::cout << "\nTesting invalid index of numbers[-2]. Should throw an error." << std::endl;
    numbers[-2] = 0;
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }

  try
  {
    std::cout << "\nTesting invalid index of numbers[MAX_VAL]. Should throw an error." << std::endl;
    numbers[MAX_VAL] = 0;
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
  
  // Randomly assign values to numbers
  for (int i = 0; i < MAX_VAL; i++)
  {
    numbers[i] = rand() % 100;
  }

  // Print out values from numbers after random assignment
  std::cout << std::endl;
  std::cout << "Numbers array after newly assigned values: " << std::endl;
  for (int i = 0; i < MAX_VAL; i++)
    std::cout << numbers[i] << " ";
  std::cout << std::endl;

  delete [] mirror;
  return 0;
}
