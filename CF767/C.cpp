#include <bits/stdc++.h>
using namespace std;

int main(){
  int t; cin >> t;
  while(t--){
    int n; cin >> n;
    vector<queue<int> > val(n+1, queue<int>());
    for(int i = 0; i<n; i++){
      int ac; cin >> ac;
      val[ac].push(i);
    }

    vector<int> ans;

    int st=0;
    int nxt=0;
    while(nxt < n){
      for(int i = 0; i<=n; i++){
	// Remove indexes used
	while(!val[i].empty() && val[i].front() < st) val[i].pop();

	if(!val[i].empty()){
	  int pos = val[i].front(); val[i].pop();
	  // pos >= st, save biggest
	  nxt = max(pos, nxt);
	} else {
	  ans.push_back(i);
	  nxt++;
	  st = nxt;
	  break;
	}
      }
    }
    cout << ans.size() << endl;
    for(int i = 0; i<ans.size(); i++){
      if(i > 0) cout << " ";
      cout << ans[i];
    }cout<<endl;
  }
}
