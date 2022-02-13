#include <bits/stdc++.h>
using namespace std;

int toint(char x){
  return x-'a';
}
char tochar(int x) {
  return 'a'+x;
}

int main(){
  int n, m; cin >> n >> m;
  string seen, ciphered;
  cin >> seen >> ciphered;

  stack<char> ans;
  queue<char> Q;
  for(int i = n-1; i>=0; i--){
    Q.push(seen[i]);
    ans.push(seen[i]);
  }

  int i = m-1;
  while(i >= n){
    char ac = Q.front(); Q.pop();
    char nxt = tochar((toint(ciphered[i])-toint(ac)+26)%26);

    ans.push(nxt);
    Q.push(nxt);
    
    i--;
  }

  while(!ans.empty()){
    char ac = ans.top(); ans.pop();
    cout << ac;
  }
  cout<<endl;
}
