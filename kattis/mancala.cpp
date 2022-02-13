#include <bits/stdc++.h>
using namespace std;
const int TEST = 1;

void print(vector<int> &ac){
  for(int i = 0;i <ac.size(); i++){
    cout << ac[i] << " ";
  }cout<<endl;
}


int main(){
  int tc; cin >> tc;
  while(tc--){
    int t, n; cin >> t >> n;

    int lvl = 1;
    while(lvl*(lvl+1)/2 < n) lvl++;

    cout << lvl<<endl;

    vector<int> ac(80, 0);
    ac[lvl-1] = lvl;
    ac[lvl-2] = lvl-2;
    print(ac);
    
  }
}
