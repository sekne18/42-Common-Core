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
    std::string date = line.substr(0, line.find("|")-1);
    try {
      if (line.find("|") == std::string::npos)
      {
        throw BitcoinExchange::BadInputException(line);
        continue;
      }

      if (valid_date(date) && valid_value(line.substr(line.find("|") + 1), date))
      {
        value = std::strtof(line.substr(line.find("|") + 1).c_str(), NULL);
        calcValues(findDate(date), value, date);
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

void BitcoinExchange::calcValues(std::string date, float values, std::string input_date)
{
  std::cout << input_date << " => " << values << " = " << _data[date] * values  << std::endl;
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
  if (date.length() != 10 || date[4] != '-' || date[7] != '-')
    throw BitcoinExchange::BadInputException(date);
  if (date[0] < '0' || date[0] > '9' || date[1] < '0' || date[1] > '9' ||
      date[2] < '0' || date[2] > '9' || date[3] < '0' || date[3] > '9' ||
      date[5] < '0' || date[5] > '1' || date[6] < '0' || date[6] > '9' ||
      date[8] < '0' || date[8] > '3' || date[9] < '0' || date[9] > '9')
    throw BitcoinExchange::BadInputException(date);
  int year = atoi(date.substr(0, 4).c_str());
  int month = atoi(date.substr(5, 2).c_str());
  int day = atoi(date.substr(8, 2).c_str());
  if (month < 1 || month > 12)
    throw BitcoinExchange::BadInputException(date);
  if (day < 1 || day > 31)
    throw BitcoinExchange::BadInputException(date);
  if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
    throw BitcoinExchange::BadInputException(date);
  if (month == 2)
  {
    if (day > 29)
      throw BitcoinExchange::BadInputException(date);
    if (day == 29 && !(year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)))
      throw BitcoinExchange::BadInputException(date);
  }
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

