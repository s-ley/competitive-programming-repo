#include <bits/stdc++.h>

using namespace std;

const int NA = -1;
const int NEW = 0;
const int IRON = 1;
const int COAL = 2;

vector<vector<int> > G, T;
vector<int> type;
vector<int> di, dc, dr;
vector<int> vis;

int main(){
  int n, iron, coal;
  cin >> n >> iron >> coal;

  type.assign(n, NEW);
  for(int i = 0; i<iron; i++){
    int nxt; cin >> nxt; nxt--;
    type[nxt] = IRON;
  }
  for(int i = 0; i<coal; i++){
    int nxt; cin >> nxt; nxt--;
    type[nxt] = COAL;
  }

  G.assign(n, vector<int>());
  T.assign(n, vector<int>());
  for(int i = 0; i<n; i++){
    int m; cin >> m;
    for(int j = 0; j<m; j++){
      int ed; cin >> ed; ed--;
      G[i].push_back(ed);
      T[ed].push_back(i);
    }
  }
  queue<int> Q;
  // iron distance
  di.assign(n, NA);
  for(int i = 0; i<n; i++){
    if(type[i] == IRON){
      di[i] = 0;
      Q.push(i);
    }
  }
  while(!Q.empty()){
    int ac = Q.front(); Q.pop();
    for(int i = 0; i<T[ac].size(); i++){
      int nxt = T[ac][i];
      if(di[nxt] == NA){
	di[nxt] = di[ac]+1;
	Q.push(nxt);
      }
    }
  }
  // coal distance
  dc.assign(n, NA);
  for(int i = 0; i<n; i++){
    if(type[i] == COAL){
      dc[i] = 0;
      Q.push(i);
    }
  }
  while(!Q.empty()){
    int ac = Q.front(); Q.pop();
    for(int i = 0; i<T[ac].size(); i++){
      int nxt = T[ac][i];
      if(dc[nxt] == NA){
	dc[nxt] = dc[ac]+1;
	Q.push(nxt);
      }
    }
  }

  // Search answer
  int ans = 1e9;
  dr.assign(n, NA);

  int nxt = 0;
  if(dc[nxt] != NA && di[nxt] != NA){
    dr[nxt] = 0;
    ans = min(ans, dr[nxt]+dc[nxt]+di[nxt]);
    Q.push(nxt);
  }

  while(!Q.empty()){
    int ac = Q.front(); Q.pop();
    for(int i = 0; i<G[ac].size(); i++){
      int nxt = G[ac][i];
      if(dr[nxt] == NA) {
	dr[nxt] = dr[ac]+1;
	if(dc[nxt] != NA && di[nxt] != NA){
	  ans = min(ans, dr[nxt]+dc[nxt]+di[nxt]);
	}
	Q.push(nxt);
      }      
    }
  }
  if(ans == 1e9)
    cout << "impossible\n";
  else
    cout << ans << "\n";
}
