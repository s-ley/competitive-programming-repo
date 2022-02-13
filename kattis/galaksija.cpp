#include <bits/stdc++.h>

using namespace std;
using ii = pair<int,int>;
using iii = pair<ii, int>;

int n;
vector<iii> inp_edg;
vector<int> inp_ord;

void read() {
  cin >> n;
  for(int i = 0; i<n-1; i++){
    int st, ed, w; cin >> st >> ed >> w;
    inp_edg.push_back(iii(ii(st-1,ed-1),w));
  }
  for(int i = 0; i<n-1; i++){
    int nxt; cin >> nxt;
    inp_ord.push_back(nxt-1);
  }
}

vector<int> uf, sz, xo;
vector<map<int, vector<int> > > paths;
long long curr;

int find(int x){
  return (uf[x]==x)? x : (uf[x] = find(uf[x]));
}

void print_list(vector<int> &l){
  for(int i = 0; i<l.size(); i++)
    cout << l[i] << " "; cout << endl;
}
void test(int a, int b, int c, int d) {
  cout << a << " " << b << endl;
  cout << c << " " << d << endl;
  cout << n << endl;
  for(int i = 0; i<n; i++){
    cout << find(i) << " ";
  }cout << endl;
  print_list(xo);
  print_list(sz);
  cout << curr << endl;
}

void init_uf(){
  curr = 0;
  uf.resize(n); sz.assign(n, 1);
  paths.resize(n);
  xo.assign(n, 0);
  for(int i = 0; i<n; i++){
    uf[i]=i;
    paths[i][0].push_back(i);
  }
}
void join(int a, int b, int w){
  if(sz[find(a)] < sz[find(b)]) swap(a,b);
  int c = find(a);
  int d = find(b);
  uf[d] = c;
  sz[c] += sz[d];

  // increment boring paths by the new paths created with this edge
  // num operations: at most half of the new merged tree size * cost of moving a node
  for(auto it : paths[d]){
    for(auto x : it.second) {
      int xo_x_to_b = xo[x]^xo[b];
      curr += paths[c][xo_x_to_b^w^xo[a]].size();
    }
  }
  
  // join small to big
  int xo_b = xo[b];
  for(auto it : paths[d]){
    for(auto x : it.second) {
      int nxt_xo = xo[x]^xo_b^w^xo[a];
      xo[x] = nxt_xo;
      paths[c][nxt_xo].push_back(x);
    }
  }
  //test(a,b,c,d);
}

int main(){
  read();
  init_uf();

  vector<long long> ans(n, 0);
  //test(0,0,0,0);
  for(int i = n-2; i>=0; i--){
    int nxt = inp_ord[i];
    int st = inp_edg[nxt].first.first, ed = inp_edg[nxt].first.second, w = inp_edg[nxt].second;
    join(st, ed, w);
    ans[i] = curr;
  }

  for(int i = 0; i<n; i++)
    cout<<ans[i]<<"\n";
			      
}
