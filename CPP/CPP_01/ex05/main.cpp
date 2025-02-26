#include "Harl.hpp"

int main()
{
  Harl harl;
  harl.complain("debug");
  harl.complain("error");
  harl.complain("info");
  harl.complain("warning");
  harl.complain("error");
  return 0;
}
