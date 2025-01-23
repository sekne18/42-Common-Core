/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 19:04:23 by jans              #+#    #+#             */
/*   Updated: 2025/01/21 19:04:25 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

int main(int ac, char **av)
{
    // Program starts and constantly prompts the user for the input.
    // The Program only accepts ADD, SEARCH and EXIT
    // ADD, saves a new contact - no empty fields!
    // SEARCH, displays a specific contact
    // EXIT, exits the program    
    PhoneBook book;

    while (1)
    {
        std::string input;
        std::cout << "Please enter a command: ADD, SEARCH or EXIT" << std::endl;
        std::cin >> input;
        if (input == "ADD")
        {
            Contact contact;
            std::cout << "Please enter the first name" << std::endl;
            std::cin >> contact.first_name;
            std::cout << "Please enter the last name" << std::endl;
            std::cin >> contact.last_name;
            std::cout << "Please enter the nickname" << std::endl;
            std::cin >> contact.nickname;
            std::cout << "Please enter the phone number" << std::endl;
            std::cin >> contact.phone_number;
            std::cout << "Please enter the darkest secret" << std::endl;
            std::cin >> contact.darkest_secret;
            book.add_contact(contact);
        }
        else if (input == "SEARCH")
        {
            std::cout << "Index     |First Name|Last Name |Nickname  " << std::endl;
            for (int i = 0; i < 8; i++)
            {
                std::cout << i << "         |";
                std::cout << contact.first_name << "         |";
                std::cout << contact.last_name << "         |";
                std::cout << contact.nickname << "         |";
                std::cout << std::endl;
            }
            std::cout << "Please enter the index of the contact you want to display" << std::endl;
            std::cin >> input;
            book.search_contact(contac);
        }
        else if (input == "EXIT")
            break;
        else
            std::cout << "Invalid command" << std::endl;
    }
    return (0);
}

// Add a new contact to the phonebook.
void PhoneBook::add_contact(Contact contact)
{
    contacts[index] = contact;
    if (index != 7)
        index++;
    return;
}

void PhoneBook::search_contact(Contact contact)
{
    // if the index is out of range, print error. Otherwise, print the contact information, onefield per line.
    if (index < 0 || index > 7)
    {
        std::cout << "Invalid index" << std::endl;
        return;
    }
    std::cout << "First Name: " << contact.first_name << std::endl;
    std::cout << "Last Name: " << contact.last_name << std::endl;
    std::cout << "Nickname: " << contact.nickname << std::endl;
    std::cout << "Phone Number: " << contact.phone_number << std::endl;
    std::cout << "Darkest Secret: " << contact.darkest_secret << std::endl;

    return;
}

PhoneBook::PhoneBook(void) {
    this->index = 0;
    return;
}

PhoneBook::~PhoneBook(void) {
    return;
}


