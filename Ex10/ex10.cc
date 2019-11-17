/*
    ex10.cc
    概要: 入力から名前, 学籍番号, 成績などの情報を出力するプログラム
    Author: Kaito Kimura
    Date: 2019/11/17
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

#define NAME_SIZE 11
#define ID_SIZE 9
#define TOTAL_SIZE 5
#define MEDIAN_SIZE 5
#define GRADE_SIZE 5
#define SPACE_SIZE 0
#define ERROR_MESSAGE " No grade"

// using name spaces
using namespace std;

// prototype definition
string fill(int size) { return string(size, ' '); };
string sep_line(int, char);
void print_sep_line(ostream &os, int count) {
  os << sep_line(count, '-') << endl;
};
void print_frame_line(ostream &os) { os << sep_line(-1, '=') << endl; };

// Student Info Class
class Student_info {
public:
  Student_info() : Mid(0), Final(0){};
  Student_info(istream &);
  string first_name() const { return FirstName; };
  string last_name() const { return LastName; };
  string id() const { return ID; };
  istream &read(istream &);
  double sum() const;
  double median();
  double total() { return Mid * 0.2 + Final * 0.4 + median() * 0.4; };
  string grade();
  bool is_valid() { return Homework.size() != 0; };
  void print_row(ostream &);
  void print_info(); // For Debug

private:
  string FirstName, LastName, ID;
  double Mid, Final;
  vector<double> Homework;
};

// functions
istream &read_hw(istream &is, vector<double> &v) {
  if (is) {
    double x;
    v.clear();
    while (is >> x) {
      v.push_back(x);
    }
    is.clear();
  }
  return is;
}

istream &Student_info::read(istream &is) {
  is >> ID >> FirstName >> LastName >> Mid >> Final;
  read_hw(is, Homework);
  return is;
}

Student_info::Student_info(istream &is) { read(is); }

void Student_info::print_info() {
  cout << "Name: " << FirstName << " " << LastName << endl;
  cout << "ID: " << ID << endl;
  cout << "Mid: " << Mid << endl;
  cout << "Final: " << Final << endl;
  cout << "Sum: " << sum() << endl;
  cout << "Median: " << median() << endl;
  cout << "Total: " << total() << endl;
  cout << "Grade: " << grade() << endl;
  cout << "Homeworks: [";
  for (int i = 0; i != (int)Homework.size(); i++) {
    cout << Homework[i];
    if (i != Homework.size() - 1) {
      cout << ", ";
    }
  }
  cout << "]" << endl;
}

double Student_info::sum() const {
  double sum_value = 0.0;
  for (int i = 0; i != (int)Homework.size(); i++) {
    sum_value += Homework[i];
  }
  return sum_value;
}

double Student_info::median() {
  int size = (int)Homework.size();

  if (size == 0) {
    return 0.0;
  };
  sort(Homework.begin(), Homework.end());

  if (size % 2 == 0) {
    // 偶数 => 中央の平均
    return (Homework[size / 2 - 1] + Homework[size / 2]) / 2;
  } else {
    // 奇数 => 中央
    return Homework[size / 2];
  }
}

string Student_info::grade() {
  double total_score = total();

  if (total_score >= 90)
    return "A";
  else if (total_score >= 80)
    return "B+";
  else if (total_score >= 70)
    return "B";
  else if (total_score >= 60)
    return "C+";
  else if (total_score >= 50)
    return "C";
  else
    return "D";
}

void Student_info::print_row(ostream &os) {
  string space = string(SPACE_SIZE, ' ');

  os << "|" << space << FirstName
     << fill(NAME_SIZE - FirstName.size() - SPACE_SIZE * 2) << space;
  os << "|" << space << LastName
     << fill(NAME_SIZE - LastName.size() - SPACE_SIZE * 2) << space;
  os << "|" << space << ID << fill(ID_SIZE - ID.size() - SPACE_SIZE * 2)
     << space;
  if (is_valid()) {
    os << "|" << space << fixed << setw(TOTAL_SIZE - SPACE_SIZE * 2)
       << setprecision(1) << median() << space;
    os << "|" << space << fixed << setw(MEDIAN_SIZE - SPACE_SIZE * 2)
       << setprecision(1) << total() << space;
    os << "|" << space << fixed << setw(GRADE_SIZE - SPACE_SIZE * 2)
       << setprecision(1) << grade() << space;
  } else {
    const string error_message = ERROR_MESSAGE;
    double sizes[] = {TOTAL_SIZE, MEDIAN_SIZE, GRADE_SIZE};
    int ignore = 3;
    int fill_num = 0;

    for (int i = 0; i != sizeof(sizes) / sizeof(*sizes); i++) {
      fill_num += sizes[i];
    }

    fill_num += (ignore - 1) - error_message.size() - SPACE_SIZE;
    os << "|" << space << error_message << fill(fill_num) << space;
  }
  os << "|" << endl;
}

// == End Student Info Class ==

string sep_line(int word_number, char sep) {
  string count_str, line;
  // count = -1: 出力しない
  count_str = word_number != -1 ? to_string(word_number) : "";
  line = "+";
  double sizes[] = {NAME_SIZE - SPACE_SIZE * 2,   NAME_SIZE - SPACE_SIZE * 2,
                    ID_SIZE - SPACE_SIZE * 2, TOTAL_SIZE - SPACE_SIZE * 2,
                    MEDIAN_SIZE - SPACE_SIZE * 2, GRADE_SIZE - SPACE_SIZE * 2};
  for (int i = 0; i != sizeof(sizes) / sizeof(*sizes); i++) {
    line += string(sizes[i], sep) + "+";
  }

  line += count_str;
  return line;
}

bool compare(const Student_info &x, const Student_info &y) {
    return x.first_name() != y.first_name() ? x.first_name() < y.first_name()
                                            : x.last_name() < y.last_name();
}

// ⇓ Main Function ⇓

int main(int argc, char *argv[]) {
  if (argc != 3) {
    cerr << "Error, Args must be input file, output file" << endl;
    return -1;
  }

  // variables
  vector<Student_info> students;
  Student_info student;
  ifstream infile(argv[1]);  // Input
  ofstream outfile(argv[2]); // Output

  while (student.read(infile)) {
    students.push_back(student);
  }

  sort(students.begin(), students.end(), compare);

  print_frame_line(outfile);
  for (int i = 0; i != (int)students.size(); i++) {
    if (i != 0 && i % 5 == 0) {
      print_sep_line(outfile, i);
    }
    students[i].print_row(outfile);
  }
  print_frame_line(outfile);

  return 0;
}
