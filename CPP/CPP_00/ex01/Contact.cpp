#include "Contact.hpp"

Contact::Contact(string first_name, string last_name, string nickname, string phone_nbr, string secret) {
  this->first_name = first_name;
  this->last_name = last_name;
  this->nickname = nickname;
  this->phone_nbr = phone_nbr;
  this->secret = secret;
}

Contact::~Contact(void) {
  return;
}

void Contact::set_first_name(string first_name) {
  this->first_name = first_name;
}

void Contact::set_last_name(string last_name) {
  this->last_name = last_name;
}

void Contact::set_nickname(string nickname) {
  this->nickname = nickname;
}

void Contact::set_phone_nbr(string phone_nbr) {
  this->phone_nbr = phone_nbr;
}

void Contact::set_secret(string secret) {
  this->secret = secret;
}

string Contact::get_first_name() {
  return this->first_name;
}

string Contact::get_last_name() {
  return this->last_name;
}

string Contact::get_nickname() {
  return this->nickname;
}

string Contact::get_phone_nbr() {
  return this->phone_nbr;
}

string Contact::get_secret() {
  return this->secret;
}


