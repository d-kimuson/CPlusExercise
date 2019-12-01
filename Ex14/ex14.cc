/*
    ex14.cc
    概要: Handle Classの追加
    Author: Kaito Kimura
    Date: 2019/12/01
*/
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

template <class T> T *clone(T *p) { return new T(*p); }

//  Put Handle class below
template <class T> class Handle {
  friend class Core;

public:
  Handle() : p(0){};
  Handle(const Handle &s) : p(0) {
    if (s.p)
      p = s.p->clone();
  }
  Handle &operator=(const Handle &);
  ~Handle() { delete p; }
  Handle(T *t) : p(t) {}
  operator bool() const { return p; }
  T &operator*() const;
  T *operator->() const;

private:
  T *p;
};

template <class T> Handle<T> &Handle<T>::operator=(const Handle<T> &rhs) {
  if (rhs != *this) {
    delete p;
    p = rhs.p ? clone(rhs.p) : 0;
  }
  return *this;
}

template <class T> T &Handle<T>::operator*() const {
  if (p)
    return *p;
  throw runtime_error("unbound Handle");
}

template <class T> T *Handle<T>::operator->() const {
  if (p)
    return p;
  throw runtime_error("unbound Handle");
}

//  Put Core class below
class Core {
public:
  Core() : midterm(0), final(0) {}
  Core(istream &is) { read(is); }
  string name() const { return n; };
  istream &read_hw(istream &, vector<double> &);
  virtual double grade() const;
  virtual istream &read(istream &);
  bool valid() { return (int)homework.size() != 0; };
  virtual Core *clone() const { return new Core(*this); }

protected:
  double midterm, final;
  vector<double> homework;
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

//  Put Grad class below
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

int main() {
  vector< Handle<Core> > students;
  Handle<Core> record;
  char ch;
  string::size_type maxlen = 0;

  while (cin >> ch) {
    if (ch == 'U') {
      record = new Core;
    } else {
      record = new Grad;
    }
    record->read(cin);
    maxlen = max(maxlen, record->name().size());
    students.push_back(record);
  }

  sort(students.begin(), students.end());
  // sort(students.begin(), students.end(), compare_Core_handles);

  for (vector< Handle<Core> >::size_type i = 0; i != students.size(); ++i) {
    cout << students[i]->name()
         << string(maxlen + 1 - students[i]->name().size(), ' ');
    if (students[i]->valid()) {
      double final_grade = students[i]->grade();
      streamsize prec = cout.precision();
      cout << setprecision(3) << final_grade << setprecision(prec);
    } else {
      cout << "Caanot evaluate";
    }
    cout << endl;
  }

  return 0;
}
