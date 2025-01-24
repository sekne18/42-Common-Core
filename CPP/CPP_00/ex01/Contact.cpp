#include "Contact.hpp"

Contact::Contact(void)
{
  return;
}

Contact::Contact(std::string first_name, std::string last_name, std::string nickname, std::string phone_nbr, std::string secret) {
  this->first_name = first_name;
  this->last_name = last_name;
  this->nickname = nickname;
  this->phone_nbr = phone_nbr;
  this->secret = secret;
}

Contact::~Contact(void) {
  return;
}

void Contact::set_first_name(std::string first_name) {
  this->first_name = first_name;
}

void Contact::set_last_name(std::string last_name) {
  this->last_name = last_name;
}

void Contact::set_nickname(std::string nickname) {
  this->nickname = nickname;
}

void Contact::set_phone_number(std::string phone_nbr) {
  this->phone_nbr = phone_nbr;
}

void Contact::set_secret(std::string secret) {
  this->secret = secret;
}

std::string Contact::get_first_name() {
  return this->first_name;
}

std::string Contact::get_last_name() {
  return this->last_name;
}

std::string Contact::get_nickname() {
  return this->nickname;
}

std::string Contact::get_phone_number() {
  return this->phone_nbr;
}

std::string Contact::get_secret() {
  return this->secret;
}


