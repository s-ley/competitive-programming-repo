#include <bits/stdc++.h>

using namespace std;
vector<string> words;

void test(vector<int> &best){
  for(int i = 0; i<best.size(); i++) cout << best[i] << " ";
  cout<<endl;
}

int max_words(vector<char> &str) {
  int sz = str.size();
  vector<int> best(sz+1, 0);
  for(int i = 1; i<=sz; i++){
    for(int j = 0; j<words.size(); j++){
      int wz = words[j].size();

      if(wz>i) continue;
      bool valid = true;
      for(int k = 0; k<wz; k++) {
	if(words[j][k] != str[i-wz+k]){
	  valid = false;
	  break;
	}
      }

      if(valid) {
	best[i] = max(best[i], best[i-wz]+1);
      }
      best[i] = max(best[i], best[i-1]);
    }
  }
  //test(best);
  return best[sz];
}

int main(){
  string tmp;
  char c;

  while(cin >> tmp) {
    if(tmp.compare("#") == 0) break;
    words.push_back(tmp);
  }

  vector<char> phrase;
  while(cin >> c) {
    if('a'<=c && c <= 'z') phrase.push_back(c);
    else if(c=='|'){
      int total = max_words(phrase);
      cout << total << "\n";
      phrase.clear();
    } else if(c == '#') {
      break;
    }
  }
}
