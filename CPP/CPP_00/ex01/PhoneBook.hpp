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

class PhoneBook {
  public:
    PhoneBook(void);
    ~PhoneBook(void);
    void add_contact(Contact contact);
    void search_contact(std::string first_name, std::string last_name);
  private:
    Contact contacts[8];:
};
