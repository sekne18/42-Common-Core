#include "Zombie.hpp"

int main(void)
{
    Zombie zombie = Zombie("Zombie1");
    zombie.announce();
    randomChump("Zombie2");
    Zombie* zombie3 = newZombie("Zombie3");
    zombie3->announce();
    delete zombie3;
    return 0;
}
