/*
    ex03.cc
    概要: list3.txt(学籍番号, 名前, 中間得点, 期末得点, 演習得点)を入力として, 各人の成績を出力するプログラム.
    Author: Kaito Kimura
    Date: 2019/10/10
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#define NAME_SIZE 13
#define NUMBER_SIZE 11
#define SUM_SIZE 7
#define AVERAGE_SIZE 7
#define MEDIAN_SIZE 7
#define GRADE_SIZE 7

// using name spaces
using namespace std;

// prototype definition
string sep_line(int, char);

void print_seq_line(int);

void print_frame_line();

string fill(int);

void print_row_data(string, string, string, double, double, double, double);

void print_vector_double(vector<double>);

int main() {
    string id, first_name, last_name;
    double sum, average, median, grade, mid, final, exercise;
    int count, index, line_count=0;
    vector<double> homework;

    print_frame_line();  // start line

    while (cin >> id >> first_name >> last_name >> mid >> final) {
        homework.clear();
        count = 0;
        sum = 0.0;
        // print separate line
        if(line_count != 0 && line_count % 5 == 0) {
            print_seq_line(line_count);
        }

        while(cin >> exercise) {
            if (exercise == -1) {
                break;
            } else {
                count++;
                sum += exercise;
                homework.push_back(exercise);
            }
        }

        // calc average
        if (count != 0) {
            average = sum / count;
        } else {
            average = 0.0;
        }

        // calc median
        sort(homework.begin(), homework.end());
        index = homework.size() / 2;

        if (homework.size() == 0) {
            median = 0.0;
        } else {
            median = homework.size() % 2 == 0 ? (homework[index-1] + homework[index]) / 2
                                              : homework[index];
        }

        // calc grade
        grade = 0.2 * mid + 0.4 * final + 0.4 * median;

        // print
        print_row_data(first_name, last_name, id, sum, average, median, grade);

        // for next loop
        line_count += 1;
    }

    print_frame_line();  // end line
    return 0;
}

string fill(int size) {
    return string(size, ' ');
}

void print_row_data(string fname, string lname, string number, double sum, double ave, double med, double grade) {
    cout << "| " << fname << fill(NAME_SIZE - fname.size() - 2) << " ";
    cout << "| " << lname << fill(NAME_SIZE - lname.size() - 2) << " ";
    cout << "| " << number << fill(NUMBER_SIZE - number.size() - 2) << " ";
    cout << "| " << fixed << setw(SUM_SIZE - 2) << setprecision(1) << sum << " ";
    cout << "| " << fixed << setw(AVERAGE_SIZE - 2) << setprecision(1) << ave << " ";
    cout << "| " << fixed << setw(MEDIAN_SIZE - 2) << setprecision(1) << med << " ";
    cout << "| " << fixed << setw(GRADE_SIZE - 2) << setprecision(1) << grade << " ";
    cout << "|" << endl;
}

string sep_line(int word_number, char sep) {
    string count_str, line;
    // count = -1: 出力しない
    count_str = word_number != -1 ? to_string(word_number)
                                  : "";
    line = "+";
    double sizes[] = {NAME_SIZE, NAME_SIZE, NUMBER_SIZE, SUM_SIZE, AVERAGE_SIZE, MEDIAN_SIZE, GRADE_SIZE};
    for(int i = 0; i != sizeof(sizes)/sizeof(*sizes); i++) {
        line += string(sizes[i], sep) + "+";
    }

    line += count_str;
    return line;
}

void print_seq_line(int word_count) {
    string line = sep_line(word_count, '-');
    cout << line << endl;
}

void print_frame_line() {
    cout << sep_line(-1, '=') << endl;
}

void print_vector_double(vector<double> array) {
    cout << "[";
    for (int i = 0; i != (int)array.size(); i++) {
        cout << array[i];
        if (i != array.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}