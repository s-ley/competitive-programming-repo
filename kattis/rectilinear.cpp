#include <bits/stdc++.h>
using namespace std;
using ii = pair<int, int>;
using di = pair<int, ii>;

const int TEST = 0;

class Solution {
private:
  vector<ii> idx_point;
  vector<di> point_idx;
  int n;
  void read() {
    idx_point.clear();
    point_idx.clear();
    cin >> n;
    for(int i = 0; i<n; i++){
      int x, y; cin >> x >> y;
      idx_point.push_back(ii(x,y));
      point_idx.push_back(di(i,ii(x,y)));
    }
  }
  vector<vector<int> > G;
  bool genGraph() {
    G.assign(n, vector<int>());
    
    if(n%2 == 1) return false;
    sort(point_idx.begin(), point_idx.end(), Solution::sortByX);
    for(int i = 0; i<n; i+=2) {
      di a = point_idx[i], b = point_idx[i+1];
      int x1 = a.second.first, x2 = b.second.first, y1 = a.second.second, y2 = b.second.second;
      if(x1 != x2) return false;
      G[a.first].push_back(b.first);
      G[b.first].push_back(a.first);
    }
    sort(point_idx.begin(), point_idx.end(), Solution::sortByY);
    for(int i = 0; i<n; i+=2) {
      di a = point_idx[i], b = point_idx[i+1];
      int x1 = a.second.first, x2 = b.second.first, y1 = a.second.second, y2 = b.second.second;
      if(y1 != y2) return false;
      G[a.first].push_back(b.first);
      G[b.first].push_back(a.first);
    }
    if(TEST >= 1) {
      printf("Points:\n");
      for(int i = 0; i<n; i++){
	printf("%d: (%d,%d), ", i, idx_point[i].first, idx_point[i].second);
      }printf("\n");
      printf("Graph:\n");
      for(int i = 0; i<n; i++){
	printf("%d:", i);
	for(int j = 0; j<G[i].size(); j++){
	  printf(" %d", G[i][j]);
	}printf("\n");
      }
    }
    return true;
  }
  bool checkNoIntersections(){
    sort(point_idx.begin(), point_idx.end(), Solution::sortByX);
    set<int> HL;
    for(int i = 0; i<n; i++){
      int idx = point_idx[i].first;
      int x = point_idx[i].second.first, y = point_idx[i].second.second;
      ii v1 = idx_point[G[idx][0]], v2 = idx_point[G[idx][1]];
      if(v1.first != x) {
	ii tmp = v1; v1=v2; v2 = tmp;
      }
      if(HL.upper_bound(min(y, v1.second)) != HL.upper_bound(max(y, v1.second)-1)) {
	if(TEST) {
	  printf("Found intersection: (%d,%d)->(%d,%d) with segment of y=%d\n", x,y,v1.first,v1.second, *HL.upper_bound(min(y, v1.second)));
	}
	return false;
      }
      if(v2.first < x) {
	HL.erase(y);
      } else {
	HL.insert(y);
      }
    }
    return true;
  }
  vector<int> V;
  int dis(ii a, ii b) {
    int dx = a.first-b.first;
    int dy = a.second-b.second;
    return abs(dx)+abs(dy); // Hamilton distance
  }
  void printPoint(ii x){
    printf("(%d,%d)", x.first, x.second);
  }
  void printLine(ii st, ii ed) {
    printPoint(st); printf("->"); printPoint(ed);
  }
  int getSumPolygon() {
    V.assign(n, 0);
    V[0] = 1;
    queue<int> Q; Q.push(0);
    int st = 0, ac = 0;
    int ans = 0;
    while(!Q.empty()) {
      ac = Q.front(); Q.pop();
      if(TEST){
	printf("Current point: ");
	printPoint(idx_point[ac]);
	printf("\n");
      }
      for(int i = 0; i<G[ac].size(); i++){
	int nxt = G[ac][i];
	if(!V[nxt]) {
	  int d = dis(idx_point[ac], idx_point[nxt]);
	  if(TEST) {
	    printf("Distance = %d. ", d);
	    printLine(idx_point[ac], idx_point[nxt]); printf("\n");
	  }
	  ans += d;
	  V[nxt] = 1;
	  Q.push(nxt);
	  break;
	}
      }
    }
    ans += dis(idx_point[st], idx_point[ac]);
    return ans;
  }
  bool allVisited() {
    for(int i = 0; i<n; i++){
      if(!V[i]) return false;
    }
    return true;
  }
public:
  static bool sortByX(di a, di b) {
    int x1 = a.second.first, x2 = b.second.first, y1 = a.second.second, y2 = b.second.second;
    return x1<x2 || (x1==x2 && y1<y2);
  }
  static bool sortByY(di a, di b) {
    int x1 = a.second.first, x2 = b.second.first, y1 = a.second.second, y2 = b.second.second;
    return y1<y2 || (y1==y2 && x1<x2);
  }
  Solution(){
  }
  int solve() {
    read();
    if(!genGraph()) return -1;
    if(!checkNoIntersections()) return -1;
    int ans = getSumPolygon();
    if(!allVisited()) return -1;
    return ans;
  }
};

int main(){
  int t; cin >> t;
  Solution *S = new Solution();
  while(t--){
    int ans = S->solve();
    printf("%d\n", ans);
  }
}
