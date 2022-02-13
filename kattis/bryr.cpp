#include <bits/stdc++.h>
using namespace std;
using ii = pair<int, int>;
const int INF = 1e9;

int main(){
  int n, m;
  cin >> n >> m;

  vector<vector<int> > G, W;
  G.assign(n, vector<int>());
  W.assign(n, vector<int>());
  for(int i  =0; i<m; i++){
    int st, ed, w; cin >> st >> ed >> w;
    st--; ed--;

    G[st].push_back(ed);
    G[ed].push_back(st);
    W[st].push_back(w);
    W[ed].push_back(w);
  }

  priority_queue<ii, vector<ii>, greater<ii> > Q;
  vector<int> D(n, INF);
  D[0] = 0;
  Q.push(ii(0, 0));

  while(!Q.empty()){
    int ac = Q.top().second;
    int d = Q.top().first;
    Q.pop();
    if(d != D[ac]) continue;

    for(int i = 0; i<G[ac].size(); i++){
      int nxt = G[ac][i];
      int w = W[ac][i];

      if(D[nxt] > D[ac]+w){
	D[nxt] = D[ac]+w;
	Q.push(ii(D[nxt], nxt));
      }
    }
  }

  cout << D[n-1] <<endl;
}
