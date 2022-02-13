#include <bits/stdc++.h>
using namespace std;

int main(){
  int t; cin >> t;
  while(t--){
    int n, m; cin >> n >> m;

    vector<int> dis;
    for(int i = 0; i<n; i++){
      for(int j = 0; j<m; j++){
	int d_x = max(i-0, n-i-1);
	int d_y = max(j-0, m-j-1);
	dis.push_back(d_x+d_y);
      }
    }
    sort(dis.begin(), dis.end());

    for(int i = 0; i<dis.size(); i++){
      if(i > 0) cout << " ";
      cout << dis[i];
    }cout<<"\n";
  }
}
