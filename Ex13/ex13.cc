/*
    ex13.cc
    概要: 入力からグレードを出力するプログラム
    Author: Kaito Kimura
    Date: 2019/11/25
*/
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

/*
  Core class
    Provide core functions for student information
*/
class Core {
  //  Put code below
  friend class Student_info;

public:
  Core() : midterm(0), final(0) {}
  Core(istream &is) { read(is); }
  string name() const { return n; };
  istream &read_hw(istream &, vector<double> &);
  virtual double grade() const;
  virtual istream &read(istream &);

protected:
  double midterm, final;
  vector<double> homework;
  virtual Core *clone() const { return new Core(*this); }
  string n;
};

double median(vector<double> v) {
  int size = (int)v.size();

  if (size == 0) {
    return 0.0;
  };
  sort(v.begin(), v.end());

  if (size % 2 == 0) {
    // 偶数 => 中央の平均
    return (v[size / 2 - 1] + v[size / 2]) / 2;
  } else {
    // 奇数 => 中央
    return v[size / 2];
  }
}

double grade(double mid, double final, const vector<double> &hw) {
  return mid * 0.2 + final * 0.4 + median(hw) * 0.4;
}

double Core::grade() const { return ::grade(midterm, final, homework); }

istream &Core::read_hw(istream &is, vector<double> &v) {
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

istream &Core::read(istream &is) {
  is >> n >> midterm >> final;
  read_hw(is, homework);
  return is;
}

/*
  Grad class
  Provide a class for a graduate student
*/
class Grad : public Core {
  // Put code below
public:
  Grad() : thesis(0) {}
  Grad(istream &is) { read(is); }
  double grade() const;
  istream &read(istream &);

private:
  double thesis;
  Core *clone() const { return new Grad(*this); }
};

istream &Grad::read(istream &in) {
  in >> n >> midterm >> final >> thesis;
  Core::read_hw(in, homework);
  return in;
}

double Grad::grade() const { return min(Core::grade(), thesis); }

/*
  Student_info class
  Provide a hundle class
*/
class Student_info {
  //  Put code below
  //  Student_info class should have valid() function
private:
  Core *cp;

public:
  Student_info() : cp(0) {}
  Student_info(istream &is) : cp(0) { read(is); }
  Student_info(const Student_info &);
  ~Student_info() { delete cp; }
  // grade関数を呼び出す
  double grade() { return cp->grade(); }
  bool valid() { return (int)cp->homework.size() != 0; }
  istream &read(istream &);
  Student_info &operator=(const Student_info &);
  string name() const {
    if (cp)
      return cp->name();
    else
      throw runtime_error("uninitialized");
  }
  static bool compare(const Student_info &s1, const Student_info &s2) {
    return s1.name() < s2.name();
  }
};

std::istream &Student_info::read(std::istream &is) {
  delete cp;
  char ch;
  is >> ch;
  if (ch == 'U') {
    cp = new Core(is);
  } else {
    cp = new Grad(is);
  }
  return is;
}

Student_info::Student_info(const Student_info &s) : cp(0) {
  if (s.cp)
    cp = s.cp->clone();
}

Student_info &Student_info::operator=(const Student_info &s) {
  if (&s != this) {
    delete cp;
    if (s.cp)
      cp = s.cp->clone();
    else
      cp = 0;
  }
  return *this;
}

/*
  main()
*/
int main(int argc, char *argv[]) {
  vector<Student_info> students;
  Student_info record;
  string::size_type maxlen = 0;

  while (record.read(cin)) {
    maxlen = max(maxlen, record.name().size());
    students.push_back(record);
  }

  sort(students.begin(), students.end(), Student_info::compare);

  for (vector<Student_info>::size_type i = 0; i != students.size(); ++i) {
    cout << students[i].name()
         << string(maxlen + 1 - students[i].name().size(), ' ');
    if (students[i].valid()) {
      double final_grade = students[i].grade();
      streamsize prec = cout.precision();
      cout << setprecision(3) << final_grade << setprecision(prec);
    } else {
      cout << "Caanot evaluate";
    }
    cout << endl;
  }

  return 0;
}
