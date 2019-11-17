/*
  ex07.cc
  概要:検索単語が出現した行番号を出力するプログラム
  Author: Kaito Kimura
  Date: 2019/11/04
*/

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cctype>
#include <map>

using namespace std;

vector<string> split(const string&);
bool is_space(char);
bool is_not_space(char);


int main(){
  string s, search_word;
  int count = 0;
  map<string, vector<int> > counters;
  vector<string> data;

  cin >> search_word;

  while(getline(cin, s)){
    data = split(s);

    for(int i = 0; i!= data.size(); i++){
      counters[data[i]].push_back(count);
    }

    count++;
  }

  cout << search_word << " is appeared at ";

  for(map<string, vector<int> >::iterator iter = counters.begin();
      iter != counters.end();
      ++iter){
    if((*iter).first == search_word){
      for(int j = 0; j<(*iter).second.size(); j++){
        cout << (*iter).second[j] << " ";
      }
    }
  }

  cout << endl;
  return 0;
}

vector<string> split(const string& s){
  int h_count, t_count;
  string::const_iterator i, j;
  vector<string> result;
  string word;


  i = s.begin();

  while(i < s.end() -1){
    h_count=0;
    t_count=0;

    word.clear();
    i = find_if(i, s.end(), is_not_space);
    j = find_if(i, s.end(), is_space);

    copy(i, j, back_inserter(word));

    for(int k = 0; k != int(word.size()); k++){
      word[k] = tolower(word[k]);
    }

    for(int k = 0; k != int(word.size()); k++) {
      if((k == 0) && ((word[k] == '\"') || (word[k] == '\'') || (word[k] == ')') || (word[k] == '.') || (word[k] == ',') || (word[k] == '('))){
        h_count++;
      } else if((k > word.size() - 3) && ((word[k] == ')') || (word[k] == '(') || (word[k] == ':') || (word[k] == '?'))){
        t_count++;
      }

      if((k == (word.size() - 1)) && ((word[k] == '\"') || (word[k] == '\'') || (word[k] == '.') || (word[k] == ','))){
        t_count++;
      }
    }

    if(h_count > 0){
      word = word.substr(1, word.size() - 1);
    }

    if(t_count > 0){
      word = word.substr(0, word.size() - t_count);
    }

    result.push_back(word);
    i = j + 1;

  }
  return result;
}

bool is_space(char c) {
  return isspace(c);
}

bool is_not_space(char c) {
  return !isspace(c);
}
