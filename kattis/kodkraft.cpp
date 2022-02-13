#include <bits/stdc++.h>
using namespace std;
using ii = pair<long long, int>;

const long long INF = 1e18;

int TEST = 0;

class Helper {
public:
  static void print(vector<int> &x) {
    for(int i = 0; i<x.size(); i++)
      cout << x[i] << " ";
    cout<<endl;
  }
  static void print(vector<long long> &x) {
    for(int i = 0; i<x.size(); i++)
      cout << x[i] << " ";
    cout<<endl;
  }
};

class Sol {
  vector<int> input;
  int n, k;
  void read() {
    cin >> n >> k;
    input.resize(n);
    for(int i = 0; i<n; i++){
      cin >> input[i];
    }
    if(TEST>=1) {
      cout << n << " " << k << endl;
      Helper::print(input);
    }
  }
  vector<int> closestDis;
  int dis(int st, int ed) {
    if(ed >= st) return ed-st;
    return n-st+ed;
  }
  void init(){
    closestDis.assign(n, 1e9);
    vector<int> lastFound(k+1, -1);
    for(int step = 0; step<2; step++)
      for(int i = n-1; i>=0; i--){
	int ac = input[i];
	// Save distance to next one
	if(ac != k && lastFound[ac+1] != -1) {
	  closestDis[i] = min(closestDis[i], dis(i, lastFound[ac+1]));
	}
	// Save position
	lastFound[ac] = i;
      }
    if(TEST>=1) {
      cout << "Closest Dis:"<<endl; 
      Helper::print(closestDis);
      cout << "Last found:"<<endl;
      Helper::print(lastFound);
    }
  }
public:
  void solve() {
    read();
    init();
    priority_queue<ii,vector<ii>, greater<ii> > Q;
    vector<long long> dis(n, INF);
    for(int i = 0; i<n; i++){
      if(input[i] == 1){
	dis[i] = 1;
	Q.push(ii(1, i));
      }
    }
    while(!Q.empty()){
      ii ac = Q.top(); Q.pop();
      int idx = ac.second;
      long long d = ac.first;
      if(dis[idx] != d || input[idx] == k) continue;

      int nxtIdx = (closestDis[idx]+idx)%n;
      long long nxtDis = d+closestDis[idx];
      if(nxtDis < dis[nxtIdx]){
	dis[nxtIdx] = nxtDis;
	Q.push(ii(nxtDis, nxtIdx));
      }
    }

    if(TEST >= 1) {
      cout << "Distances:"<<endl;
      Helper::print(dis);
    }

    long long ans = INF;
    for(int i = 0; i<n; i++){
      if(input[i] == k){
	ans = min(ans, dis[i]);
      }
    }
    cout << ans<<endl;
  }

};

int main(){
  Sol S;
  S.solve();
}
