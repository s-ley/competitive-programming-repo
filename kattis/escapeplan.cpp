#include<bits/stdc++.h>
using namespace std;
using dd = pair<double, double>;

const int TEST = 0;

vector<dd> rb, ho;
vector<vector<int> > G, W, R;
int s, t;

vector<int> P, I;
const int EMPTY = -1;
bool flowExists() {
  P.assign(G.size(), EMPTY);
  I.assign(G.size(), EMPTY);
  P[s] = s;
  queue<int> Q; Q.push(s);
  while(!Q.empty()){
    int ac = Q.front(); Q.pop();
    for(int i = 0; i<G[ac].size(); i++){
      int nxt = G[ac][i];
      int nxtD = W[ac][i];
      if(P[nxt] == EMPTY && nxtD > 0){
	P[nxt] = ac;
	I[nxt] = i;
	Q.push(nxt);
      }
    }
  }
  if(TEST) {
    //cout << "flowExists()"<<endl;
  }
  return P[t] != EMPTY;
}
int getFlow(){
  int maxV = 0;
  int ac = t;
  while(P[ac] != ac) {
    int p = P[ac];
    maxV = max(maxV, W[p][I[ac]]);
    ac = P[ac];
  }

  ac = t;
  while(P[ac] != ac) {
    int p = P[ac];
    W[p][I[ac]] -= maxV;
    W[ac][R[p][I[ac]]] += maxV;
    ac = P[ac];
  }

  return maxV;
}

int mf() {
  int ans = 0;
  while(true){
    bool ok = flowExists();
    if(!ok) break;
    int val = getFlow();
    ans += val;
  }
  return ans;
}


double dis(dd a, dd b){
  double dx = a.first-b.first;
  double dy = a.second-b.second;
  return sqrt(dx*dx + dy*dy);
}

void add_edge(int v1, int v2, int w){
  int rfront = G[v2].size(), rback = G[v1].size();
  G[v1].push_back(v2);
  W[v1].push_back(w);
  R[v1].push_back(rfront);
  G[v2].push_back(v1);
  W[v2].push_back(0);
  R[v2].push_back(rback);
}

void init(double d) {
  int total = rb.size() + ho.size() + 2;
  G.assign(total, vector<int>());
  W.assign(total, vector<int>());
  R.assign(total, vector<int>());

  s = total-2; t = total-1;

  // From s to robots
  for(int i = 0; i<rb.size(); i++){
    add_edge(s, i, 1);
  }

  // From holes to t
  for(int i = 0; i<ho.size(); i++){
    add_edge(rb.size()+i, t, 1);
  }

  // from robots to holes
  for(int i = 0; i<rb.size(); i++){
    for(int j = 0; j<ho.size(); j++){
      if(dis(rb[i],ho[j]) <= d) {
	add_edge(i, rb.size()+j, 1);
      }
    }
  }

  if(TEST){
    printf("GRAPH:\ns=%d, t=%d\n", s, t);
    for(int i  =0; i<total; i++){
      printf("%d:", i);
      for(int j = 0; j<G[i].size(); j++){
	printf(" (%d,%d,%d)", G[i][j], W[i][j], R[i][j]);
      }
      printf("\n");
    }
  }
}

int main(){
  int n, m;
  int tc = 1;
  while(cin >> n && n){
    rb.clear();
    ho.clear();

    for(int i = 0; i<n; i++){
      dd nxt; cin >> nxt.first >> nxt.second;
      rb.push_back(nxt);
    }
    cin >> m;
    for(int i = 0; i<m; i++){
      dd nxt; cin >> nxt.first >> nxt.second;
      ho.push_back(nxt);
    }

    if(TEST){
      printf("ROBOTS:\n");
      for(int i = 0; i<rb.size(); i++){
	printf("(%lf,%lf) ", rb[i].first, rb[i].second);
      }printf("\n");
      printf("HOLES:\n");
      for(int i = 0; i<ho.size(); i++){
	printf("(%lf,%lf) ", ho[i].first, ho[i].second);
      }printf("\n");

    }

    cout << "Scenario "<< tc << "\n"; tc++;
    
    init(50.0);
    cout << "In 5 seconds "<< mf() << " robot(s) can escape\n";
    init(100.0);
    cout << "In 10 seconds "<< mf() << " robot(s) can escape\n";
    init(200.0);
    cout << "In 20 seconds "<< mf() << " robot(s) can escape\n";
    cout << "\n";
  }
}
