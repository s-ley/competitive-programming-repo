#include <bits/stdc++.h>
using namespace std;

const int TEST = 0;
const int UNS = 2;
void print(vector<int> &x){
  for(int i = x.size()-1;i>=0; i--){
    if(x[i] == 2) cout << "?";
    else cout << x[i];
  }cout <<endl;
}

int main(){
  int n;
  while(cin >> n && n){
    vector<int> ac(32, UNS);
    for(int i = 0; i<n; i++){
      string op; int a, b;
      cin >> op;

      if(op == "CLEAR"){
	cin >> a;
	ac[a] = 0;
      } else if(op == "SET"){
	cin >> a;
	ac[a] = 1;
      } else if(op == "OR"){
	cin >> a >> b;
	if(ac[b] == 1) ac[a] = 1;
	else if(ac[b] == UNS && ac[a] == 0) ac[a] = UNS;
      } else if(op == "AND"){
	cin >> a >> b;
	if(ac[b] == 0) ac[a] = 0;
	else if(ac[b] == UNS && ac[a] == 1) ac[a] = UNS;
      }
      if(TEST){
	print(ac);
      }
    }
    print(ac);
  }
}
