/*
    ex01.cc
    概要: Ex01
    Author: Kaito Kimura
    Date: 2019-10-03
*/

#include <iostream>

int main() {
  std::string first_name;  // 名: first name
  std::string last_name;  // 性: last name

  // Input
  std::cout << "Pleaes input your first name >> ";
  std::cin >> first_name;
  std::cout << "Pleaes input your last name >> ";
  std::cin >> last_name;

  // Output
  std::cout << "**************************" << std::endl;
  std::cout << "*                        *" << std::endl;
  std::cout << "* Hello, " << last_name << " " << first_name << "! *" << std::endl;
  std::cout << "*                        *" << std::endl;
  std::cout << "**************************" << std::endl;

  return 0;
}
