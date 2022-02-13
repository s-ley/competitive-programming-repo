#include <bits/stdc++.h>
using namespace std;

int getpow(int v, int p) {
  int st = 1;
  for(int i = 1; i<=p; i++)
    st *= v;
  return st;
}

int main(){
  int c, k;
  cin >> c >> k;

  if(k==0){
    cout << c << endl;
    return 0;
  }

  int pot = getpow(10, k);
  int res = c%pot;
  if(res < pot/2)
    c -= res;
  else {
    c -= res;
    c += pot;
  }
  cout << c << endl;
}
