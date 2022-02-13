#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
  int n; cin >> n;
  vector<ll> inp;
  for(int i = 0; i<n; i++){
    ll nxt; cin >> nxt;
    if(nxt) inp.push_back(nxt);
  }

  ll sum = 0;
  for(int i = 0; i<inp.size(); i++){
    sum += (i+1)*inp[i];
  }

  // 0 at end
  ll best = sum;
  for(int i = 0; i<inp.size(); i++){
    sum += inp[inp.size()-1-i];
    best = max(best, sum);
  }

  cout << best <<endl;
}
