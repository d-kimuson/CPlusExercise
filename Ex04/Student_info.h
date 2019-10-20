/*
    Student_info.h
    概要: Student_info.ccのヘッダファイル
    Author: Kaito Kimura
    Date: 2019/10/17
*/


#include <iostream>
#include <vector>

// using name spaces
using namespace std;

// Student Info Dininition
struct Student_info {
    string ID;
    string First_Name; // 姓
    string Last_Name; // 名
    double Midterm; // 中間試験の成績:
    double Final; // 期末試験の成績:
    vector<double> Exercise; // 演習の成績:
};

// prototype difinition
bool compare(const Student_info &, const Student_info &);
istream &read(istream &, Student_info &);
istream &read_hw(istream &, vector<double> &);
double median(vector<double>);
double grade(double, double, const vector<double> &, double &, double &, double &);