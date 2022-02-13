#include <bits/stdc++.h>
using namespace std;
void print(vector<int> &ac){
  for(int i = 0; i<ac.size(); i++){
    cout << ac[i] << " ";
  }cout<<endl;
}
int main(){
  int t; cin >> t;
  for(int tc = 1; tc<=t; tc++){
    int n; cin >> n;
    vector<int> R, B;
    for(int i = 0; i<n; i++){
      string str; cin >> str;

      int l; char c;
      stringstream ss(str); ss >> l >> c;
      if(c=='R')
	R.push_back(l-1);
      else
	B.push_back(l-1);
    }

    sort(R.begin(), R.end(), greater<int>());
    sort(B.begin(), B.end(), greater<int>());

    int ans = 0;
    for(int i = 0; i<min(B.size(), R.size()); i++){
      ans += B[i] + R[i];
    }

    //print(B); print(R);
    cout << "Case #"<<tc<<": "<< ans << endl;
  }
}
