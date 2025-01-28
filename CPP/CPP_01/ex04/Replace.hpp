
#ifndef REPLACE_HPP
#define REPLACE_HPP

#include <string>
#include <iostream>
#include <fstream>

class Replace
{
public:
  void replace(const std::string &filename, const std::string &word, const std::string &newWord);

private:  
  std::string readFromFile(const std::string &filename);
  void writeToFile(const std::string &filename, const std::string &content);

};

#endif
