#include <bits/stdc++.h>
using namespace std;

int main(){
  int R;
  string res;
  cin >> R;

  int lo=1,hi=R;
  int day = 1;
  while(true){
    int nxt = (lo+hi)/2;
    cout << nxt*day <<endl << flush;

    cin >> res;
    if(res == "exact") break;
    if(res == "less") hi = nxt-1;
    if(res == "more") lo = nxt+1;

    day++;
  }
}
