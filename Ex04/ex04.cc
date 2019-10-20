/*
    ex04.cc
    概要: 成績を入力に成績を計算して出力するプラグラム
    Author: Kaito Kimura
    Date: 2019/10/17
*/

#include "Student_info.h"
#include <iomanip>
#include <algorithm>

#define NAME_SIZE 13
#define NUMBER_SIZE 11
#define SUM_SIZE 7
#define AVERAGE_SIZE 7
#define MEDIAN_SIZE 7
#define GRADE_SIZE 7

// prototype definition
string sep_line(int, char);
void print_seq_line(int);
void print_frame_line();
string fill(int);
void print_row_data(Student_info, double, double, double, double, bool);
void print_vector_double(vector<double>);


int main() {
    vector<Student_info> students;
    Student_info record;
    // まずデータの読み込み
    while (read(cin, record)) {
        students.push_back(record);
    }
    // 学生データを名前順にソート
    sort(students.begin(), students.end(), compare);

    // 学生のデータを出力
    print_frame_line();  // start line
    for (vector<Student_info>::size_type i = 0; i != students.size(); ++i) {
        if (i != 0 && i % 5 == 0) {
            print_seq_line(i);
        }

        // 総合得点，演習メジアン，演習平均，演習合計
        double total, ex_med, ex_avg, ex_sum;
        // 計算
        // grade関数の中で例外が発生するかもしれないので
        try {
            total = grade(students[i].Midterm,
                          students[i].Final, students[i].Exercise,
                          ex_med, ex_avg, ex_sum);
            // 画面にデータを出力（ここでは省略）
            print_row_data(students[i], ex_sum, ex_avg, ex_med, total, false);
        } catch (std::domain_error) {
            // ここに例外時の処理を書く
            // 今回はID, First_Name, LastNameの後に，
            // 演習回数が0だから総合得点が計算できない
            // というエラーメッセージを出力
            print_row_data(students[i], ex_sum, ex_avg, ex_med, total, true);
        }
    }
    print_frame_line();  // end line
    return 0;
}

string fill(int size) {
    return string(size, ' ');
}

void print_row_data(Student_info s, double sum, double ave, double med, double grade, bool is_error) {
    cout << "| " << s.First_Name << fill(NAME_SIZE - s.First_Name.size() - 2) << " ";
    cout << "| " << s.Last_Name << fill(NAME_SIZE - s.Last_Name.size() - 2) << " ";
    cout << "| " << s.ID << fill(NUMBER_SIZE - s.ID.size() - 2) << " ";
    if (!is_error) {
        cout << "| " << fixed << setw(SUM_SIZE - 2) << setprecision(1) << sum << " ";
        cout << "| " << fixed << setw(AVERAGE_SIZE - 2) << setprecision(1) << ave << " ";
        cout << "| " << fixed << setw(MEDIAN_SIZE - 2) << setprecision(1) << med << " ";
        cout << "| " << fixed << setw(GRADE_SIZE - 2) << setprecision(1) << grade << " ";
    } else {
        const string error_message = "no exercises";
        int fill_num = SUM_SIZE + AVERAGE_SIZE + MEDIAN_SIZE + GRADE_SIZE - error_message.size() - 2 + 3;
        // sum(sizes) + message_size - space + sep line
        cout << "| " << error_message
             << fill(fill_num) << " ";
    }
    cout << "|" << endl;
}

string sep_line(int word_number, char sep) {
    string count_str, line;
    // count = -1: 出力しない
    count_str = word_number != -1 ? to_string(word_number)
                                  : "";
    line = "+";
    double sizes[] = {NAME_SIZE, NAME_SIZE, NUMBER_SIZE, SUM_SIZE, AVERAGE_SIZE, MEDIAN_SIZE, GRADE_SIZE};
    for (int i = 0; i != sizeof(sizes) / sizeof(*sizes); i++) {
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
    for (int i = 0; i != (int) array.size(); i++) {
        cout << array[i];
        if (i != array.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}