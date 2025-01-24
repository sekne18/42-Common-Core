/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 12:56:04 by jans              #+#    #+#             */
/*   Updated: 2025/01/02 12:56:06 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <iomanip>
#include "Contact.hpp"

class PhoneBook {
  public:
    PhoneBook(void);
    ~PhoneBook(void);
    void add_contact(Contact contact);
    void search_contact(int index);
    void print_contacts();
  private:
    Contact contacts[8];
    int index;
};
