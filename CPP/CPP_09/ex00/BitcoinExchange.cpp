#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(std::string inputFile) : _inputFile(inputFile)
{
  loadDatabase();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
  *this = other;
}

BitcoinExchange::~BitcoinExchange()
{
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
  if (this != &other)
  {
    _inputFile = other._inputFile;
    _data = other._data;
  }
  return *this;
}

void BitcoinExchange::loadDatabase()
{
  float value;
  std::string line;
  std::ifstream file("data.csv");
  std::getline(file, line);
  while (std::getline(file, line))
  {
    value = std::strtof(line.substr(line.find(",") + 1).c_str(), NULL);
    _data[line.substr(0, line.find(","))] = value;
  }
  file.close();
}

void BitcoinExchange::processFile()
{
  float value;
  std::string line;
  std::string last_date;
  std::ifstream file(_inputFile.c_str());
  std::getline(file, line);
  while (std::getline(file, line))
  {
    std::string date = line.substr(0, line.find("|"));
    try {
      if (valid_date(date) && valid_value(line.substr(line.find("|") + 1), date))
      {
        value = std::strtof(line.substr(line.find("|") + 1).c_str(), NULL);
        calcValues(findDate(date), value);
      }
    }
    catch (const NotPositiveException &e) {
      std::cout << e.what() << std::endl;
      continue;
    }
    catch (const TooLargeException &e) {
      std::cout << e.what() << std::endl;
      continue;
    }
    catch (const BadInputException &e) {
      std::cout << e.what() << std::endl;
      continue;
    }
  }
  file.close();
}

void BitcoinExchange::calcValues(std::string date, float values)
{
  std::cout << date << "=>" << values << " = " << _data[date] * values  << std::endl;
}

std::string BitcoinExchange::findDate(std::string date)
{
  std::string last_date;
  for(std::map<std::string, float>::iterator it = _data.begin(); it != _data.end(); it++)
  {
    if (date == it->first)
      return it->first;
    else if (date > it->first)
      last_date = it->first;
    else if (date < it->first)
      return last_date;
  }
  return last_date;
}

bool BitcoinExchange::valid_date(std::string date)
{
  // split string by -
  // validate each value range
  (void)date;
  return true;
}

bool BitcoinExchange::valid_value(std::string value, std::string date)
{
  float f;
  char* endptr;
  
  f = std::strtof(value.c_str(), &endptr);
  if (endptr == value.c_str() || *endptr != '\0')
    throw BitcoinExchange::BadInputException(date);
  if (f < 0)
    throw BitcoinExchange::NotPositiveException();
  if (f > 1000)
    throw BitcoinExchange::TooLargeException();
  return true;
}

void BitcoinExchange::print_data()
{
  for(std::map<std::string, float>::iterator it = _data.begin(); it != _data.end(); it++) {
      std::cout << it->first << "," << it->second << std::endl;
  }
}

const char *BitcoinExchange::TooLargeException::what() const throw()
{
  return "Error: too large a number.";
}

const char *BitcoinExchange::NotPositiveException::what() const throw()
{
  return "Error: not a positive number.";
}

BitcoinExchange::BadInputException::BadInputException(const std::string& msg)
    : _msg("Error: bad input => " + msg) {}

BitcoinExchange::BadInputException::~BadInputException() throw() {}

const char *BitcoinExchange::BadInputException::what() const throw()
{
  return _msg.c_str();
}

