#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using dl = pair<ll, ll>;
using dli = pair<dl, int>;

const int TEST = 0;

class Helper{
public:
  static void print(dli &nxt) {
    printf("(%d, (%lld,%lld))", nxt.second, nxt.first.first, nxt.first.second);
  }
  static void print(vector<dli> &L){
    for(int i = 0; i<L.size(); i++){
      Helper::print(L[i]);
      printf(" ");
    }
    printf("\n");
  }
  static void print(vector<int> &L) {
    for(int i = 0; i<L.size(); i++){
      printf("%d ", L[i]);
    }
    printf("\n");
  }
  static void print(vector<vector<int> > &G){
    for(int i = 0; i<G.size(); i++){
      printf("%d: ", i);
      Helper::print(G[i]);
    }
  }
};

const int UP=0,DOWN=1,LEFT=2,RIGHT=3;
class DIR {
public:
  static int get(dl &a, dl &b) {
    ll dx = a.first-b.first;
    ll dy = a.second-b.second;
    if(dx != 0 && dy != 0) return -1;
    if(dx == 0){
      return dy>0? UP : DOWN;
    }
    return dx>0? RIGHT : LEFT;
  }
};

bool secondLexComp(dli &a, dli &b) {
  if(a.first.second < b.first.second) return true;
  if(a.first.second == b.first.second) return a.first.first < b.first.first;
  return false;
}
bool resetList(dli &a, dli &b) {
  return a.second < b.second;
}

class Sol {
private:
  int n;
  vector<dli> input;
  dl start, fin;
  void read(){
    scanf("%d", &n);
    scanf("%lld %lld %lld %lld", &start.first, &start.second, &fin.first, &fin.second);
    
    input.resize(n);
    for(int i = 0; i<n; i++){
      scanf("%lld %lld", &input[i].first.first, &input[i].first.second);
      input[i].second = i;
    }
  }
  vector<vector<int> > G1;
  void genG1(){
    G1.assign(n, vector<int>());
    sort(input.begin(), input.end());
    for(int i = 0; i<n-1; i++){
      dli ac = input[i], nxt = input[i+1];
      int dir = DIR::get(ac.first, nxt.first);
      if(TEST >= 2) {
	printf("AC: ");
	Helper::print(ac);
	printf("\nNxt: ");
	Helper::print(nxt);
	printf("\nDir: %d\n", dir);
      }
      if(dir == UP || dir == DOWN){
	G1[ac.second].push_back(nxt.second);
	G1[nxt.second].push_back(ac.second);
      }
    }
    if(TEST) {
      printf("Sort 1:\n");
      Helper::print(input);
    }
    sort(input.begin(), input.end(), secondLexComp);
    for(int i = 0; i<n-1; i++){
      dli ac = input[i], nxt = input[i+1];
      int dir = DIR::get(ac.first, nxt.first);
      if(dir == LEFT || dir == RIGHT){
	G1[ac.second].push_back(nxt.second);
	G1[nxt.second].push_back(ac.second);
      }
    }
    if(TEST) {
      printf("Sort 2:\n");
      Helper::print(input);
      printf("G:\n");
      Helper::print(G1);
    }
    sort(input.begin(), input.end(), resetList);
    if(TEST) {
      printf("Reset:\n");
      Helper::print(input);
    }
  }
  vector<vector<int> > G2;
  int getInDir(int ac, int DIR) {
    if(ac == -1) return -1;
    dl p1 = input[ac].first;
    for(int i = 0; i<G1[ac].size(); i++) {
      int nxt = G1[ac][i];
      dl p2 = input[nxt].first;
      if(DIR::get(p1, p2) == DIR) {
	return nxt;
      }
    }
    return -1;
  }
  int getSequence(int ac, int d1, int d2, int d3) {
    return getInDir(getInDir(getInDir(ac,d1),d2),d3);
  }
  void genG2() {
    G2.assign(n, vector<int>());
    vector<vector<int> > movements = {
      { UP, UP, LEFT },
      { UP, UP, RIGHT },
      { DOWN, DOWN, LEFT },
      { DOWN, DOWN, RIGHT },
      { LEFT, LEFT, UP },
      { LEFT, LEFT, DOWN },
      { RIGHT, RIGHT, UP },
      { RIGHT, RIGHT, DOWN }
    };
    for(int i = 0; i<n; i++){
      int op;
      for(int j = 0; j<movements.size(); j++){
	op = getSequence(i, movements[j][0], movements[j][1], movements[j][2]);
	if(op != -1){
	  G2[i].push_back(op);
	}
      }
    }
    if(TEST) {
      printf("G2:\n");
      Helper::print(G2);
    }
  }
public:
  void solve() {
    read();
    genG1();
    genG2();
    int s,t;
    for(int i = 0; i<n; i++){
      if(start.first == input[i].first.first && start.second == input[i].first.second) {
	s = i;
      }
      if(fin.first == input[i].first.first && fin.second == input[i].first.second) {
	t = i;
      }
    }
    const int INF = 1e9;
    vector<int> dis(n, INF);
    queue<int> Q;
    dis[s] = 0;
    Q.push(s);
    while(!Q.empty()){
      int ac = Q.front(); Q.pop();
      for(int i = 0; i<G2[ac].size(); i++){
	int nxt = G2[ac][i];
	if(dis[nxt] == INF){
	  dis[nxt] = dis[ac]+1;
	  Q.push(nxt);
	}
      }
    }
    if(TEST){
      Helper::print(dis);
    }
    if(dis[t] == INF)
      printf("-1\n");
    else
      printf("%d\n", dis[t]);
  }
};

int main(){
  Sol S;
  S.solve();
}
