#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using dl = pair<ll, ll>;
using ddl = pair<dl, ll>;

const int TEST = 0;

class Helper {
public:
  static ll readMili() {
    char input[10];
    scanf("%s", input);

    int dotPos = -1;
    int endPos = strlen(input);
    for(int i = 0; i<10; i++){
      if(input[i] == '.') dotPos = i;
    }
    ll ans = 0;
    int st = (input[0] == '-')? 1 : 0;
    for(int i = st; i<endPos; i++){
      if(input[i] != '.') {
	ans *= 10;
	ans += (input[i]-'0');
      }
    }

    int missing = 3-(endPos-dotPos-1);
    while(missing--){
      ans*=10;
    }
    if(input[0] == '-') ans *=-1;
    
    return ans;
  }
  static void print(ddl X) {
    printf("((%lld,%lld),%lld)", X.first.first, X.first.second, X.second);
  }
  static void print(vector<ddl> X) {
    for(int i = 0; i<X.size(); i++){
      Helper::print(X[i]);
      printf("\n");
    }
  }
  static void print(vector<int> L) {
    for(int i = 0; i<L.size(); i++){
      printf("%d ", L[i]);
    }
    printf("\n");
  }
  static void print(vector<vector<int> > G) {
    for(int i = 0; i<G.size(); i++){
      printf("%d: ", i);
      Helper::print(G[i]);
    }
  }
};

class CircleData {
private:
  ll squaredDis(dl a, dl b){
    ll dx = a.first-b.first;
    ll dy = a.second-b.second;
    return dx*dx+dy*dy;
  }
public:
  vector<ddl> circles; 
  void read(int n) {
    circles.clear();
    for(int i = 0; i<n; i++){
      ll x, y, r;
      x = Helper::readMili();
      y = Helper::readMili();
      r = Helper::readMili();
      circles.push_back(ddl(dl(x,y), r));
    }
    if(TEST) {
      printf("%d\n", n);
      Helper::print(circles);
    }
  }
  bool intersect(int id1, int id2) {
    ll sumR = circles[id1].second + circles[id2].second;
    ll subR = circles[id1].second - circles[id2].second;
    ll dis2 = squaredDis(circles[id1].first, circles[id2].first);
    return sumR*sumR > dis2 && subR*subR < dis2;
  }
};

class Sol {
  CircleData inputData;
  vector<vector<int> > G;
  void init(int n) {
    inputData.read(n);
    G.assign(n, vector<int>());

    for(int i = 0; i<n; i++){
      for(int j = i+1; j<n; j++){
	if(inputData.intersect(i,j)) {
	  G[i].push_back(j);
	  G[j].push_back(i);
	}
      }
    }

    if(TEST) {
      Helper::print(G);
    }
  }
public:
  void solve(){
    int n;
    scanf("%d", &n);
    while(n != -1){
      init(n);

      vector<int> vis(n);
      int ans = 0;
      for(int i = 0; i<n; i++){
	if(!vis[i]){
	  vis[i] = 1;
	  int tmp = 1;
	  queue<int> Q;
	  Q.push(i);
	  while(!Q.empty()){
	    int ac = Q.front(); Q.pop();
	    for(int j = 0; j<G[ac].size(); j++){
	      int nxt = G[ac][j];
	      if(!vis[nxt]){
		vis[nxt] = 1;
		tmp++;
		Q.push(nxt);
	      }
	    }
	  }
	  ans = max(ans, tmp);
	}
      }
      printf("The largest component contains %d ring", ans);
      if(ans > 1) printf("s");
      printf(".\n");

      scanf("%d", &n);
    }
  }
};

int main(){
  Sol S;
  S.solve();
}
