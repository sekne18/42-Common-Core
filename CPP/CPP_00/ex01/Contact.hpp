/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 12:56:24 by jans              #+#    #+#             */
/*   Updated: 2025/01/02 12:56:25 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

class Contact {
  public:
    Contact(std::string first_name, std::string last_name, std::string nickname, std::string phone_nbr, std::string secret);
    Contact(void);
    ~Contact(void);
    void set_first_name(std::string first_name);
    void set_last_name(std::string last_name);
    void set_nickname(std::string nickname);
    void set_phone_number(std::string number);
    void set_secret(std::string secret);
    std::string get_first_name();
    std::string get_last_name();
    std::string get_nickname();
    std::string get_phone_number();
    std::string get_secret();
    

  private:
    std::string first_name;
    std::string last_name;
    std::string nickname;
    std::string phone_nbr;
    std::string secret;
};
