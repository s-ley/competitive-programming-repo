#include <bits/stdc++.h>
using namespace std;

const int BAD = 1;
const int VIS = 2;
const int ROT = 3;
const int PBAD = 4;

const bool TEST = false;

vector<vector<int> > G, R;
vector<int> state;
int n, e, m;

void visitAll(int st) {
  for(int i = 0; i<(int)G[st].size(); i++){
    int nxt = G[st][i];
    if(!state[nxt] || state[nxt] == ROT){
      state[nxt] = VIS;
      visitAll(nxt);
    }
  }
}
void test(){
  for(int i = 0; i<n; i++){
    cout << state[i] << " ";
  }
  cout <<endl;
}

int main(){
  cin >> n >> e >> m;
  G.assign(n, vector<int>());
  R.assign(n, vector<int>());
  for(int i = 0; i<m; i++){
    int st, ed; cin >> st >> ed;
    G[st].push_back(ed);
    R[ed].push_back(st);

    if(TEST){
      cout << st << " " << ed << endl;
    }
  }
  state.assign(n, 0);

  queue<int> Q;
  for(int i =0; i<e; i++){
    int nxt; cin >> nxt;
    state[nxt] = BAD;
    Q.push(nxt);
  }

  if(TEST) test();

  // Propagate bad
  while(!Q.empty()){
    int ac = Q.front(); Q.pop();
    for(int i = 0; i<(int)R[ac].size(); i++){
      int nxt = R[ac][i];
      if(!state[nxt]){
    state[nxt] = PBAD;
    Q.push(nxt);
      }
    }
  }

  if(TEST) test();

  vector<int> copyState = state;

  stack<int> S;
  for(int i = 0; i<n; i++){
    if(!state[i]){
      S.push(i);
      state[i] = VIS;
      visitAll(i);
      state[i] = ROT;
      if(TEST){
	cout << "i="<<i<<" propagated"<<endl;
	test();
      }
    }
  }

  state = copyState;
  while(!S.empty()) {
    int ac = S.top(); S.pop();
    if(!state[ac]) {
      state[ac] = VIS;
      visitAll(ac);
      state[ac] = ROT;
    }
  }

  int ans = 0;
  for(int i = 0; i<n; i++){
    if(state[i] == PBAD || state[i] == ROT) ans++;
  }
  cout << ans << "\n";
}
