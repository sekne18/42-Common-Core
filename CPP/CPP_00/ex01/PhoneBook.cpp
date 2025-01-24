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

// Add a new contact to the phonebook.
void PhoneBook::add_contact(Contact contact)
{
    contacts[index] = contact;
    if (index != 7)
        index++;
    return;
}

void PhoneBook::print_contacts()
{
    int i;
    // Each column should be only 10 characters wide. If longer, truncate and add a dot.
    // Print the index, first name, last name and nickname of each contact.
    // The text must be right-aligned.
 
    std::cout << "     Index|First Name| Last Name|  Nickname" << std::endl;
    i = -1;
    while (++i < 8)
    {
        std::cout << "         " << i << "|";
        std::string first_name = contacts[i].get_first_name();
        if (first_name.length() > 10)
        {
            first_name = first_name.substr(0, 9) + ".";
        }
        std::cout << std::setw(10) << std::right << first_name << "|";
        std::string last_name = contacts[i].get_last_name();
        if (last_name.length() > 10)
        {
            last_name = last_name.substr(0, 9) + ".";
        }
        std::cout << std::setw(10) << std::right << last_name << "|";
        std::string nickname = contacts[i].get_nickname();
        if (nickname.length() > 10)
        {
            nickname = nickname.substr(0, 9) + ".";
        }
        std::cout << std::setw(10) << std::right << nickname << "|";
        std::cout << std::endl;
    }
    
}

void PhoneBook::search_contact(int index)
{
    // if the index is out of range, print error. Otherwise, print the contact information, onefield per line.
    if ((index < 0 || index > 7) || this->index < index)
    {
      std::cout << "Invalid index" << std::endl;
        return;
    }
    
    std::cout << "First Name: " << contacts[index].get_first_name() << std::endl;
    std::cout << "Last Name: " << contacts[index].get_last_name() << std::endl;
    std::cout << "Nickname: " << contacts[index].get_nickname() << std::endl;
    std::cout << "Phone Number: " << contacts[index].get_phone_number() << std::endl;
    std::cout << "Darkest Secret: " << contacts[index].get_secret() << std::endl;

    return;
}

PhoneBook::PhoneBook(void) {
    this->index = 0;
    return;
}

PhoneBook::~PhoneBook(void) {
    return;
}


