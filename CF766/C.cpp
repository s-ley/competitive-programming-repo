#include <bits/stdc++.h>
using namespace std;
using ii = pair<int,int>;

int main(){
  int t; cin >> t;
  while(t--){
    int n; cin >> n;

    vector<ii> E(n-1);
    vector<int> W(n-1, 0);
    vector<int> D(n, 0);
    vector<vector<int> > POS(n, vector<int>());
    for(int i = 0; i<n-1; i++){
      int st, ed;
      cin >> st >> ed; st--; ed--;
      E[i] = ii(st,ed);
      D[st]++; D[ed]++;
      POS[st].push_back(i);
      POS[ed].push_back(i);
    }

    bool ok = true;
    for(int i = 0; i<n; i++){
      if(D[i] > 2){
	ok = false;
	break;
      }
    }

    if(!ok){
      cout << "-1\n";
      continue;
    }

    // DFS over edges
    queue<int> Q;
    Q.push(0);
    W[0] = 2;
    
    while(!Q.empty()){
      int idx1 = Q.front(); Q.pop();
      int st = E[idx1].first, ed = E[idx1].second;
      int w = W[idx1];

      // check one side
      for(int i = 0; i<POS[st].size(); i++){
	int idx2 = POS[st][i];
	int st2 = E[idx2].first, ed2 = E[idx2].second;
	int w2 = W[idx2];
	if(w2 == 0){
	  if(w == 2)
	    W[idx2] = 3;
	  else
	    W[idx2] = 2;
	  Q.push(idx2);
	}
      }
      // Other side
      for(int i = 0; i<POS[ed].size(); i++){
	int idx2 = POS[ed][i];
	int st2 = E[idx2].first, ed2 = E[idx2].second;
	int w2 = W[idx2];
	if(w2 == 0){
	  if(w == 2)
	    W[idx2] = 3;
	  else
	    W[idx2] = 2;
	  Q.push(idx2);
	}
      }
    }

    for(int i = 0; i<n-1; i++){
      if(i > 0) cout << " ";
      cout << W[i];
    }
    cout <<"\n";
    //*/
  }
}
