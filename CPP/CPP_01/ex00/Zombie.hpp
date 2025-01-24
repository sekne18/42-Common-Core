#include <iostream>

class Zombie
{
  public:
    Zombie(std::string name);
    ~Zombie();
    void announce(void);
    void setName(std::string name);
    std::string getName(void);
    newZombie(std::string name);
    randomChump(std::string name);

  private:
    std::string name;
};
