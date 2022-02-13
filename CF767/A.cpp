#include <bits/stdc++.h>
using namespace std;
using ii = pair<int,int>;

int main(){
  int t; cin >> t;
  while(t--){
    int n, k; cin >> n >> k;
    vector<ii> inp(n);
    for(int i = 0; i<n; i++){
      cin >> inp[i].first;
    }
    for(int i = 0; i<n; i++)
      cin >> inp[i].second;
    sort(inp.begin(), inp.end());
    for(int i = 0; i<n; i++){
      int ned = inp[i].first;
      if(ned > k) break;
      k += inp[i].second;
    }
    cout << k << endl;
  }
}
