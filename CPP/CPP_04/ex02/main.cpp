#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main()
{
  // Exercice example
	const AAnimal* dog = new Dog();
	const AAnimal* cat = new Cat();
	// const  AAnimal *d = new AAnimal();

	std::cout << std::endl;

	delete dog;
	delete cat;

	std::cout << std::endl;
	std::cout << std::endl;

	// Array of animals
	const AAnimal	*(animal_array[4]);
	std::cout << std::endl;
	// Half filled with dogs
	for (int i = 0; i < 2; i++)
		animal_array[i] = new Dog();
	std::cout << std::endl;

	// Half filled with cats
	for (int i = 2; i < 4; i++)
		animal_array[i] = new Cat();
	std::cout << std::endl;

	for (int i = 0; i < 4; i++)
		delete animal_array[i];
	std::cout << std::endl;
  return 0;
}
