#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e3;
const int C = 1e4;
const int MOD = 1e9+7;
const int UNS = -1;
const int TEST = 0;

vector<vector<ll> > DP(N+3, vector<ll>(C+3, UNS));
ll f(int n, int c){
  if(DP[n][c] != UNS) return DP[n][c];
  if(c == 0) return 1;
  if(n == 1) return 0;

  ll ans = 0;
  for(int i = 0; i<n; i++){
    if(c >= i)
    ans = (ans+f(n-1,c-i))%MOD;
  }
  DP[n][c] = ans;

  if(TEST){
    cout << "DP["<<n<<"]["<<c<<"]="<<ans<<endl;
  }
  
  return ans;
}

int main(){
  
  int n, c;
  cin >> n >> c;
  cout << f(n,c)<<endl;
}
