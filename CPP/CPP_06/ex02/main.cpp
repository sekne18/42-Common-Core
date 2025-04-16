#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <cstdlib>
#include <ctime>

Base *generate(void)
{
  // Get a different random number each time the program runs
  std::srand(time(0));

  // Generate a random number between 0 and 100
  int randomNum = std::rand() % 3;
  if (randomNum == 0)
    return (new A());
  else if (randomNum == 1)
    return (new B());
  else
    return (new C());  
}

void identify(Base* p)
{
  if (dynamic_cast<A*>(p))
    std::cout << "A" << std::endl;
  else if (dynamic_cast<B*>(p))
    std::cout << "B" << std::endl;
  else if (dynamic_cast<C*>(p))
    std::cout << "C" << std::endl; 
  else std::cout << "Unknown\n";
}

void identify(Base& p)
{
  try {
    A& a = dynamic_cast<A&>(p);
    (void)a;
    std::cout << "A" << std::endl;
    return; 
  }
  catch (const std::exception &e) {}

  try {
    B& b = dynamic_cast<B&>(p);
    (void)b;
    std::cout << "B" << std::endl;
    return; 
  }
  catch (const std::exception &e) {}

  try {
    C& c = dynamic_cast<C&>(p);
    (void)c;
    std::cout << "C" << std::endl;
    return; 
  }
  catch (const std::exception &e) {}
}

int main()
{
  Base *ptr = generate();
	Base &ref = *ptr;
	identify(ptr);
	identify(ref);
	delete ptr;
  return (0);
}
