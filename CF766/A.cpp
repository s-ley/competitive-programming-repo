#include <bits/stdc++.h>
using namespace std;

int main(){
  int t; cin >> t;
  while(t--){
    int n, m, x, y;
    cin >> n >> m >> x >> y;

    x--;y--;

    vector<vector<char> > mat(n, vector<char>(m));
    vector<int> rows(n, 0), cols(m, 0);
    char nxt;
    bool oneBlack = false;
    for(int i = 0; i<n; i++){
      for(int j  =0; j<m; j++){
	cin >> mat[i][j];
	if(mat[i][j] == 'B'){
	  oneBlack = true;
	  rows[i] = 1;
	  cols[j] = 1;
	}
      }
    }
    /*
    for(int i = 0; i<n; i++) cout << rows[i] << " "; cout<<endl;
    for(int i = 0; i<m; i++){
      cout << cols[i] << " ";
    }cout<<endl;
    //*/

    if(!oneBlack){
      cout << "-1\n";
    } else {
      if(mat[x][y] == 'B'){
	cout << "0\n";
      }else if(rows[x] || cols[y]){
	cout << "1\n";
      } else {
	cout << "2\n";
      }
    }
  }
}
