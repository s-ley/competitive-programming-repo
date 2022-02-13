#include <bits/stdc++.h>
using namespace std;

int main(){
  int t; cin >> t;
  while(t--){
    int l, r, k; cin >> l >> r >> k;

    int dis = r-l+1;
    if(dis == 1) {
      if(l == 1){
	cout << "NO\n";
      } else {
	cout << "YES\n";
      }
      continue;
    }

    // greater than 1, count odd numbers
    int odd;
    if(l%2){
      // First odd
      odd = (dis+1)/2;
    } else {
      odd = dis/2;
    }

    if(odd > k){
      cout << "NO\n";
    } else {
      cout << "YES\n";
    }
  }
}
