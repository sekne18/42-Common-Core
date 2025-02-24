#include "PhoneBook.hpp"

int main()
{
  PhoneBook book;
  while (1)
  {
    std::string input;
    std::cout << "Please enter a command: ADD, SEARCH or EXIT" << std::endl;
    std::cin >> input;
    if (std::cin.eof())
      break;
    if (input == "ADD")
    {
      Contact contact;
      std::string tmp;
      std::cout << "Please enter the first name" << std::endl;
      std::cin >> tmp;
      contact.set_first_name(tmp);
      std::cout << "Please enter the last name" << std::endl;
      std::cin >> tmp;
      contact.set_last_name(tmp);
      std::cout << "Please enter the nickname" << std::endl;
      std::cin >> tmp;
      contact.set_nickname(tmp);
      std::cout << "Please enter the phone number" << std::endl;
      std::cin >> tmp;
      contact.set_phone_number(tmp);
      std::cout << "Please enter the darkest secret" << std::endl;
      std::cin >> tmp;
      contact.set_secret(tmp);
      book.add_contact(contact);
    }
    else if (input == "SEARCH")
    {
      int input_idx;
      book.print_contacts();
      std::cout << "Please enter the index of the contact you want to display" << std::endl;
      std::cin >> input_idx;
      if (std::cin.fail())
      {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Invalid index" << std::endl;
        continue;
      }
      book.search_contact(input_idx);
    }
    else if (input == "EXIT")
      break;
    else
      std::cout << "Invalid command: " << input << std::endl;
  }
  return (0);
}
