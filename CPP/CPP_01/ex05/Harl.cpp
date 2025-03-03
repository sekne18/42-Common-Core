#include "Harl.hpp"

void Harl::debug(void)
{
  std::cout << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-specialketchup burger. I really do!" << std::endl;
}

void Harl::error(void)
{
  std::cout << "This is unacceptable! I want to speak to the manager now." << std::endl;
}

void Harl::info(void)
{
  std::cout << "I cannot believe adding extra bacon costs more money. You didn’t put enough bacon in my burger! If you did, I wouldn’t be asking for more!" << std::endl;
}

void Harl::warning(void)
{
  std::cout << "I think I deserve to have some extra bacon for free. I’ve been coming for years whereas you started working here since last month" << std::endl;
}

Harl::Harl()
{
  
}

Harl::~Harl()
{
  
}

void Harl::complain(std::string level)
{
  int i;

  i = 0;
  std::string levels[4] = {"debug", "error", "info", "warning"};
  void (Harl::*logs[4])() = {&Harl::debug, &Harl::error, &Harl::info, &Harl::warning};

  while (i < 4)
  {
    if (level == levels[i])
      break;
    i++;
  }
  
  switch (i)
  {
    case 0:
      (this->*logs[0])();
      break;
    case 1:
      (this->*logs[1])();
      break;
    case 2:
      (this->*logs[2])();
      break;
    case 3:
      (this->*logs[3])();
      break;
    default:
      break;
  }
}
