/*
    ex02.cc
    概要: 学籍番号・性・名を入力し, 整形して出力するプログラム
    Author: Kaito Kimura
    Date: 2019-10-07
*/

#include <iostream>

// using name spaces
using std::cout;
using std::endl;
using std::string;

// prototype definition
string fill_space(string, int);

void print_table(string, string, string);

void print_sep_line(int);


int main() {
    string id, first_name, last_name;
    int count = 0;

    // Start Line
    print_sep_line(-1);

    // Write Tables
    while (std::cin >> id >> first_name >> last_name) {
        if (count % 5 == 0) {
            if (count != 0) {
                print_sep_line(count);
            }
        }
        print_table(id, first_name, last_name);
        count++;
    }

    // End Line
    print_sep_line(-1);
    return 0;
}

string fill_space(string content, int size) {
    return " " + content + std::string(size - content.size() - 1, ' ');
}

void print_table(string id, string first_name, string last_name) {
    const int name_table_size = 22;
    const int number_table_size = 19;

    // First Name
    cout << "|" << fill_space(first_name, name_table_size);
    // Second Name
    cout << "|" << fill_space(last_name, name_table_size);
    // Number
    cout << "|" << fill_space(id, number_table_size) << "|" << endl;
}

void print_sep_line(int word_number) {
    // count = -1: 出力しない
    string count_str = (word_number != -1) ? std::to_string(word_number)
                                           : "";
    cout << "+======================+======================+===================+" << count_str << endl;
}