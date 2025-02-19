#ifndef HARL_HPP
#define HARL_HPP

#include <iostream>
#include <string>

class Harl
{
private:
  void debug(void);
  void error(void);
  void info(void);
  void warning(void);
  int getLevel(std::string level);
  std::string tolower(std::string level);

public:
  void complain(std::string level);
  Harl();
  ~Harl();

};

#endif // HARL_HPP
