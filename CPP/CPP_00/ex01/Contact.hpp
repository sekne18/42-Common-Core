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
    Contact(string first_name, string last_name, string nickname, string phone_nbr, string secret);
    ~Contact(void);
    void set_first_name(string first_name);
    void set_last_name(string last_name);
    void set_nickname(string nickname);
    void set_phone_nbr(string number);
    void set_secret(string secret);
    string get_first_name();
    string get_last_name();
    string get_nickname();
    string get_phone_number();
    string get_secret();
    

  private:
    string first_name;
    string last_name;
    string nickname;
    string phone_nbr;
    string secret;
};
