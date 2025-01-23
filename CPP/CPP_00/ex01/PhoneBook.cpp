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
    

    
    while (1)
    {
        std::string input;
        PhoneBook book;
        std::cout << "Please enter a command: ADD, SEARCH or EXIT" << std::endl;
        std::cin >> input;
        if (input == "ADD")
        {

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
    std::cout << "" << std::endl;
    return (0);
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


