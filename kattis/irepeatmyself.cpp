#include <bits/stdc++.h>
using namespace std;

int toInt(string s){
  stringstream ss(s);
  int ans; ss >> ans;
  return ans;
}

bool valid(int x, string &s) {
  for(int i = 0; i<s.size(); i++){
    if(s[i] != s[i%x]) return false;
  }
  return true;
}

int main(){
  string line;
  getline(cin, line);
  int n = toInt(line);

  for(int i = 0; i<n; i++){
    getline(cin, line);
    int ans = 1;
    while(!valid(ans, line)) ans++;
    cout << ans <<endl;
  }
}
