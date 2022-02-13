#include <bits/stdc++.h>
using namespace std;

const int K = 10;
const int M = 100;
const int TEST = 1;

int DP[K+1][M+1][M+1];
int best[K+1][M+1][M+1];

int f(int x) { return x*(x+1)/2; }

int solution(int k, int st, int ed) {
  if(k == 1){
    int ans = f(ed) - f(st-1);
    if(TEST >= 2){
      cout << "solution("<<k<<","<<st<<","<<ed<<")="<<ans<<endl;
    }
    return ans;
  }
  else if(DP[k][st][ed] != 0) return DP[k][st][ed];

  if(ed-st+1 <= 2){
    int ans = 0;
    for(int i = st; i<=ed; i++)
      ans += i;
    DP[k][st][ed] = ans;
    if(TEST >= 2){
      cout << "solution("<<k<<","<<st<<","<<ed<<")="<<ans<<endl;
    }
    return ans;
  }

  int ans = 1e9;
  for(int i = st+1; i<=ed-1; i++){
    int ac = i;
    int bh = solution(k-1, st, i-1);
    int ah = solution(k, i+1, ed);
    ac = ac + max(bh, ah);
    ans = min(ans, ac);
  }
  DP[k][st][ed] = ans;
  if(TEST >= 2){
    cout << "solution("<<k<<","<<st<<","<<ed<<")="<<ans<<endl;
  }
  return ans;
}

int main(){
  int t; cin >> t;
  while(t--){
    int k, m;
    cin >> k >> m;
    int ans = solution(k, 1, m);
    cout << ans << endl;
  }
}
