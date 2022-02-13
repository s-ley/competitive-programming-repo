#include <bits/stdc++.h>
using namespace std;
using ii = pair<int, int>;

const int N = 1e3;
const int INF = 1e9;
const int NINF = -1e9;
int n, m, q, s;

int W[N][N];
vector<ii> E;
vector<vector<int> > G;
vector<int> dis;

void init(){
  G.assign(n, vector<int>());
  E.clear();
  dis.assign(n, INF);
  for(int i = 0; i<N; i++)
    for(int j = 0; j<N; j++)
      W[i][j] = INF;
}


void solve() {
  dis[s] = 0;

  for(int i = 0; i<n-1; i++){
    for(int j = 0; j<E.size(); j++){
      int st = E[j].first;
      int ed = E[j].second;

      if(dis[st] != INF)
	dis[ed] = min(dis[ed], dis[st]+W[st][ed]);
    }
  }
  
  queue<int> Q;
  for(int j = 0; j<E.size(); j++){
      int st = E[j].first;
      int ed = E[j].second;

      if(dis[st] != INF && dis[ed] > dis[st]+W[st][ed]){
	dis[ed] = NINF;
	Q.push(ed);
      }
  }

  while(!Q.empty()){
    int ac = Q.front(); Q.pop();
    for(int i = 0; i<G[ac].size(); i++){
      int nxt = G[ac][i];
      if(dis[nxt] != NINF){
	dis[nxt] = NINF;
	Q.push(nxt);
      }
    }
  }
}

void test(){
  for(int i  =0; i<n; i++)
    cout << dis[i] << " ";
  cout << endl;
}

int main(){
  int tc = 0;
  while(cin >> n >> m >> q >> s && n){
    if(tc > 0) cout << "\n";
    tc++;
    
    init();

    for(int i = 0; i<m; i++){
      int st, ed, w;
      cin >> st >> ed >> w;
      E.push_back(ii(st, ed));
      G[st].push_back(ed);
      W[st][ed] = min(w, W[st][ed]);
    }

    solve();
    //test();

    for(int i  =0; i<q; i++){
      int p; cin >> p;
      if(dis[p] == INF)
	cout << "Impossible";
      else if(dis[p] == NINF)
	cout << "-Infinity";
      else
	cout << dis[p];
      cout << "\n";
    }
  }
}
