#include <bits/stdc++.h>
using namespace std;
using ii = pair<int,int>;
using di = pair<int, ii>;

const int TEST = 0;

class Solution {
private:
  vector<di> input;
  int n;
  void read() {
    cin >> n;
    input.assign(n+1, di(0, ii(0,0)));
    for(int i = 1; i<=n; i++){
      int nxt; cin >> nxt;
      input[i].first = nxt;
    }
    for(int i = 1; i<=n; i++){
      int nxt; cin >> nxt;
      input[i].second.first = nxt;
    }
    for(int i = 1; i<=n; i++){
      int nxt; cin >> nxt;
      input[i].second.second = nxt;
    }
    if(TEST) {
      for(int i = 1; i<=n; i++){
	cout << input[i].first << " ";
      }cout<<endl;
      for(int i = 1; i<=n; i++){
	cout << input[i].second.first << " ";
      }cout<<endl;
      for(int i = 1; i<=n; i++){
	cout << input[i].second.second << " ";
      }cout<<endl;
    }
  }
  vector<int> col, R2, R3;
  int ans;
  queue<int> D;
  void removeCol(int v) {
    ans++;
    col[v] = 0;
    D.push(v);
  }
  
public:
  int solve() {
    read();
    sort(input.begin(), input.end());
    ans = 0;
    col.assign(n+1, 1);
    R2.assign(n+1, 0);
    R3.assign(n+1, 0);
    while(!D.empty()) D.pop();
    
    for(int i = 1; i<=n; i++){
      R2[input[i].second.first]++;
      R3[input[i].second.second]++;
    }

    for(int i = 1; i<=n; i++) {
      if(R2[i] == 0 && col[i]){
	removeCol(i);
      }
      if(R3[i] == 0 && col[i]){
	removeCol(i);
      }
    }
    while(!D.empty()){
      int ac = D.front(); D.pop();
      int nxt = input[ac].second.first;
      R2[nxt]--;
      if(R2[nxt] == 0 && col[nxt]) {
	removeCol(nxt);
      }
      nxt = input[ac].second.second;
      R3[nxt]--;
      if(R3[nxt] == 0 && col[nxt]) {
	removeCol(nxt);
      }
    }
    return ans;
  }
};


int main(){
  Solution *s = new Solution();

  int ans = s->solve();
  cout << ans <<"\n";

}
