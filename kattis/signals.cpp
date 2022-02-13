#include <bits/stdc++.h>
using namespace std;

int main(){
  int n;
  cin >> n;
  vector<int> ans;
  vector<int>::iterator it;

  for(int i = 0; i<n; i++){
    int nxt; cin >> nxt;

    it = lower_bound(ans.begin(), ans.end(), nxt);

    if(it == ans.end()){
      ans.push_back(nxt);
    } else {
      ans[it-ans.begin()] = nxt;
    }
    
  }
  cout << ans.size() << "\n";
}
