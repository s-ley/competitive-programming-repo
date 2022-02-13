#include <bits/stdc++.h>
using namespace std;

bool isArrow(string &a){
  return a.size() == 2 && a[0] == '-' && a[1]=='>';
}

int main(){
  set<string> conclusions;
  int n; cin >> n;

  int error = -1;
  for(int i = 1; i<=n; i++){
    string tmp;
    while(cin >> tmp && !isArrow(tmp)) {
      if(conclusions.find(tmp) == conclusions.end()){
	error = i;
	break;
      }
    }
    if(error != -1) break;
    cin >> tmp;
    conclusions.insert(tmp);
  }

  if(error == -1) cout << "correct\n";
  else cout << error << endl;
}
