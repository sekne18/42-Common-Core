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

std::string Harl::tolower(std::string str)
{
  int i = 0;

  while (str[i])
  {
    if (str[i] >= 'A' && str[i] <= 'Z')
      str[i] += 32;
    i++;
  }
  return str;
}

int Harl::getLevel(std::string level)
{
  int i = 0;
  std::string levels[4] = {"info", "debug", "warning", "error"};

  while (i < 4)
  {
    if (level == levels[i])
      break;
    i++;
  }
  return i;
}

/*
* Function receives a log level and prints the corresponding message
* It should print level above the given level as well
* for example, if the log level is info, it should print info, warning, error and debug
* Uses switch case to call the corresponding function
 * */
void Harl::complain(std::string level)
{
  void (Harl::*logs[4])() = {&Harl::debug, &Harl::error, &Harl::info, &Harl::warning};
  switch (getLevel(tolower(level)))
  {
    case 1:
      std::cout << "[ DEBUG ]" << std::endl;
      (this->*logs[1])();
      std::cout << std::endl;
      std::cout << "[ INFO ]" << std::endl;
      (this->*logs[2])();
      std::cout << std::endl;
      std::cout << "[ WARNING ]" << std::endl;
      (this->*logs[3])();
      std::cout << std::endl;
      break;
    case 3:
      std::cout << "[ ERROR ]" << std::endl;
      (this->*logs[3])();
      std::cout << std::endl;
      break;
    case 0:
      std::cout << "[ INFO ]" << std::endl;
      (this->*logs[0])();
      std::cout << std::endl;
      std::cout << "[ DEBUG ]" << std::endl;
      (this->*logs[1])();
      std::cout << std::endl;
      std::cout << "[ WARNING ]" << std::endl;
      (this->*logs[2])();
      std::cout << std::endl;
      std::cout << "[ ERROR ]" << std::endl;
      (this->*logs[3])();
      std::cout << std::endl;
      break;
    case 2:
      std::cout << "[ WARNING ]" << std::endl;
      (this->*logs[2])(); 
      std::cout << std::endl;
      std::cout << "[ ERROR ]" << std::endl;
      (this->*logs[3])();
      std::cout << std::endl;
      break;
    default:
      std::cout << "[ Probably complaining about insignificant problems ]" << std::endl;
      return;
  }
}
