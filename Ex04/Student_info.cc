/*
    Student_info.cc
    概要: Student_info構造体と関連関数の定義
    Author: Kaito Kimura
    Date: 2019/10/17
*/

#include "Student_info.h"

bool compare(const Student_info &x, const Student_info &y) {
    return x.First_Name != y.First_Name ? x.First_Name < y.First_Name
                                        : x.Last_Name < y.Last_Name;
}

istream &read(istream &is, Student_info &s) {
    is >> s.ID >> s.First_Name >> s.Last_Name;
    is >> s.Midterm >> s.Final;
    // 演習の得点の読み込み, 別の関数にする
    read_hw(is, s.Exercise);
    return is;
}

istream &read_hw(istream &is, vector<double> &v) {
    if (is) {
        double x; // 毎回の演習の成績
        v.clear();
        while (is >> x) {
            v.push_back(x);
        }
        is.clear();
    }
    return is;
}

double median(vector<double> v) {
    int size = (int) v.size(), mid;
    if (size == 0) {
        throw domain_error("要素数が0のメジアン");
    }
    sort(v.begin(), v.end());
    mid = size / 2;
    return size % 2 == 0 ? (v[mid] + v[mid - 1]) / 2
                         : v[mid];
}

double
grade(double midterm, double final, const vector<double> &hw, double &ex_med, double &ex_avg, double &ex_sum) {
    if (hw.size() == 0) throw std::domain_error("演習回数が0");
    ex_med = median(hw);
    ex_sum = 0;
    for (vector<double>::size_type i = 0; i != hw.size(); ++i) {
        ex_sum += hw[i];
    }
    ex_avg = ex_sum / hw.size();
    return 0.2 * midterm + 0.4 * final + 0.4 * ex_med;
}