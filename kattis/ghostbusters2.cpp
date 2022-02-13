#include <bits/stdc++.h>
using namespace std;
using ii = pair<int,int>;
using dii = pair<double, ii>;

void test(vector<vector<int> > &ac, vector<ii> &ans, vector<vector<double> > &mat){
  for(int i  =0; i<ac.size(); i++){
    for(int j = 0; j<ac[0].size(); j++)
      cout << ac[i][j] << " ";
    cout << endl;
  }
  cout << endl;

  for(int i = 0; i<mat.size(); i++){
    for(int j = 0; j<mat[0].size(); j++){
      cout << mat[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;
  for(int i = 0; i<ans.size(); i++)
    cout << ans[i].first << "," << ans[i].second << endl;
}
vector<int> uf;
int find(int x){
  return (uf[x]==x)? x : (uf[x] = find(uf[x]));
}
bool same(int a, int b){
  return find(a) == find(b);
}
void join(int a, int b){
  if(same(a,b)) return;
  int c = find(a);
  int d = find(b);
  uf[c] = d;
}

int main(){
  int n, m;
  cin >> n >> m;

  vector<vector<double> > mat(n, vector<double>(m));
  vector<vector<int> > active(n, vector<int>(m, 0));

  for(int i = 0; i<n; i++)
    for(int j = 0; j<m; j++) cin >> mat[i][j];

  for(int i = 0; i<n; i++){
    int tmp; cin >> tmp;
    for(int j = 0; j<tmp; j++){
      int pos; cin >> pos;
      active[i][pos] = 1;
    }
  }

  vector<ii> ans;
  vector<int> rep(m, -1);

  for(int col = 0; col<m; col++){
    double mx = -1;
    ii best = ii(-1,-1);
    for(int row = 0; row<n; row++){
      if(active[row][col] && mat[row][col] > mx){
	mx = mat[row][col];
	best = ii(row,col);
      }
    }
    if(mx > 0){
      ans.push_back(best);
      active[best.first][best.second] = 0;
      rep[col] = best.first;
    }
  }
  //test(active, ans, mat);

  priority_queue<dii> conns;
  for(int i = 0; i<n; i++)
    for(int j = 0; j<m; j++)
      if(active[i][j])
	conns.push(dii(mat[i][j], ii(i,j)));

  uf.resize(n);
  for(int i=0; i<n; i++){
    uf[i]= i;
  }

  while(!conns.empty()){
    dii nxt = conns.top(); conns.pop();
    int row = nxt.second.first;
    int col = nxt.second.second;
    if(!same(row, rep[col])){
      join(row, rep[col]);
      ans.push_back(nxt.second);
    }
  }

  sort(ans.begin(), ans.end());
  for(int i  =0; i<ans.size(); i++){
    cout << ans[i].first << " " << ans[i].second <<"\n";
  }
}
