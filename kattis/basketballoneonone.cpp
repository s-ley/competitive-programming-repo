#include <bits/stdc++.h>
using namespace std;

bool ended(int a, int b) {
  return abs(a-b)>=2 && (a>=11 || b>=11);
}

int main(){
  char p; int v;

  int a = 0;
  int b = 0;
  while(!ended(a,b)){
    cin >> p >> v;
    if(p == 'A')
      a += v;
    else
      b += v;
  }

  if( a > b)
    cout << "A\n";
  else
    cout << "B\n";
}
