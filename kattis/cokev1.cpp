#include <bits/stdc++.h>
using namespace std;
using ii = pair<int, int>;
using di = pair<int, ii>;

const int C=150,P1=500,P5=100,P10=50;
const int INF = 1e9;
const int TEST = 1;

const int EXTRA = 10;

vector<vector<vector<vector<int> > > > DP(C+EXTRA, vector<vector<vector<int> > >(P1+P5+P10*2+EXTRA, vector<vector<int> >(P5+P10+EXTRA, vector<int>(P10+EXTRA,INF))));
int n, p1, p5, p10;

void read(){
  cin >> n >> p1 >> p5 >> p10;
}
int find(int tot, int ones, int fives, int tens) {
  if(TEST) {
    printf("find(%d,%d,%d,%d)=%d\n", tot,ones,fives,tens,DP[tot][ones][fives][tens]);
  }

  if(tot == 0) return 0;
  bool impossible =
    !(tens > 0 || fives > 1 || (fives == 1 && ones > 2) || ones>7);
  if(impossible) return INF;
  if(DP[tot][ones][fives][tens] < INF) return DP[tot][ones][fives][tens];

  if(tens >= 1) {
    if(ones >= 3){
      DP[tot][ones][fives][tens] = min(DP[tot][ones][fives][tens], find(tot-1, ones-3, fives+1, tens-1)+4);
    } else {
      DP[tot][ones][fives][tens] = min(DP[tot][ones][fives][tens], find(tot-1, ones+2, fives, tens-1)+1);
    }
  }
  if(fives >= 2){
    if(ones >= 3){
      DP[tot][ones][fives][tens] = min(DP[tot][ones][fives][tens], find(tot-1, ones-3, fives-2+1, tens)+5);
    } else {
      DP[tot][ones][fives][tens] = min(DP[tot][ones][fives][tens], find(tot-1, ones+2, fives-2, tens)+2);
    }
  }
  if(fives >=1 && ones >=3){
    DP[tot][ones][fives][tens] = min(DP[tot][ones][fives][tens], find(tot-1, ones-3, fives-1, tens)+4);
  }
  if(ones >= 8)
    DP[tot][ones][fives][tens] = min(DP[tot][ones][fives][tens], find(tot-1, ones-8, fives, tens)+8);

  if(TEST) {
    printf("find(%d,%d,%d)=%d\n", tot,ones,fives,DP[tot][ones][fives][tens]);
  }

  return DP[tot][ones][fives][tens];
}
int solve() {
  if(n < p10) return n;
  return find(n, p1, p5, p10);
}

int main(){

  int tc; cin >> tc;
  while(tc--){
    read();
    int ans = solve();
    cout << ans<<endl;
  }
}
