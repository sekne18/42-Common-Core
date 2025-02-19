#include "Replace.hpp"

void Replace::replace(const std::string &filename, const std::string &word, const std::string &newWord)
{
  std::string content = readFromFile(filename);
  size_t pos = 0;
  while ((pos = content.find(word, pos)) != std::string::npos)
  {
    content = content.substr(0, pos) + newWord + content.substr(pos + word.length());
    pos += newWord.length();
  }
  writeToFile(filename, content);
}

std::string Replace::readFromFile(const std::string &filename)
{
  std::ifstream ifs(filename.c_str());
  if (!ifs)
  {
    return "";
  }
  std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
  return content;
}

void Replace::writeToFile(const std::string &filename, const std::string &content)
{
  std::ofstream ofs(filename.c_str());
  if (!ofs)
  {
    return ;
  }
  ofs << content;
}
