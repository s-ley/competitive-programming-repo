#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e3;
const int C = 1e4;
const int MOD = 1e9+7;

vector<vector<ll> > DP;
vector<vector<ll> > S;
void init(int lvl) {
  S[lvl][0] = DP[lvl][0];
  for(int i = 1; i<=C; i++){
    S[lvl][i] = (S[lvl][i-1] + DP[lvl][i])%MOD;
  }
}
ll sum(int lvl, int st, int ed) {
  ll p1 = (st-1 < 0)? 0 : S[lvl][st-1];
  return (S[lvl][ed]-p1+MOD)%MOD;
}
void solve() {
  DP.assign(N+3, vector<ll>(C+3, 0));
  S.assign(N+3, vector<ll>(C+3,0));
  DP[1][0] = 1;
  DP[2][0] = 1;
  DP[2][1] = 1;
  for(int i = 3; i<=N; i++){
    // Accumulated sum on last level
    init(i-1);
    // solve f(i, C)
    for(int c = 0; c<=C; c++){
      // sum from DP[i-1][c-n+1] to DP[i-1][c]
      // st = c-(n-1)
      // ed = c
      DP[i][c] = sum(i-1, c-i+1, c);
    }
  }
}

int main(){
  int n, c; cin >> n >> c;
  solve();
  cout << DP[n][c]<<endl;
}
