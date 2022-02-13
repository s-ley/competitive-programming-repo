#include <bits/stdc++.h>
using namespace std;
using ii = pair<int, int>;

vector<vector<char> > input;
int n;
int total = 0;
vector<vector<int> > idx;

int s, t;
vector<vector<ii> > G;
vector<vector<int> > R;

void print_point(int x, int y){
  cout << "("<<x<<","<<y<<")";
}
void test() {
  cout << n << endl;
  for(int i = 0; i<input.size(); i++){
    for(int j = 0; j<input[0].size(); j++)
      cout << input[i][j];
    cout<<endl;
  }
  cout<<endl;
  cout << "IDX:"<<endl;
  for(int i = 0; i<n+1; i++){
    for(int j = 0; j<n+1; j++){
      cout << idx[i][j] << " ";
    }
    cout<<endl;
  }
  cout<<endl;
  cout << "Graph:"<<endl;
  for(int pos = 0; pos<G.size(); pos++){
    cout << pos << ": ";
    for(int k = 0; k<G[pos].size(); k++){
      int nxt = G[pos][k].first;
      int w = G[pos][k].second;
      cout << "(i="<<k<<",idx="<<nxt<<",w="<<w<<") ";
    }
    cout<<endl;
  }
  cout<<endl;
}

void joinNodes(int st, int ed, int w1, int w2){
  int pos_st = G[st].size(), pos_ed = G[ed].size();
  G[st].push_back(ii(ed, w1));
  G[ed].push_back(ii(st, w2));
  R[st].push_back(pos_ed);
  R[ed].push_back(pos_st);
}
bool validUp(int row, int col){
  return input[row*2-2][col*2-1]=='.';
}
bool validDown(int row, int col){
  return input[row*2][col*2-1]=='.';
}
bool validLeft(int row, int col){
  return input[row*2-1][col*2-2]=='.';
}
bool validRight(int row, int col){
  return input[row*2-1][col*2]=='.';
}
void joinDown(int row, int col) {
  if(validDown(row, col))
    joinNodes(idx[row][col], idx[row+1][col], 1, 1);
}
void joinRight(int row, int col){
  if(validRight(row, col))
    joinNodes(idx[row][col], idx[row][col+1], 1, 1);
}
void joinUp(int row, int col){
  if(validUp(row,col))
    joinNodes(idx[row][col], idx[row-1][col], 1, 1);
}
void joinLeft(int row, int col){
  if(validLeft(row,col))
    joinNodes(idx[row][col], idx[row][col-1], 1, 1);
}


vector<int> parent;
vector<int> index_used;
void print_flow(){
  for(int i = 0; i<parent.size(); i++){
    cout << parent[i] << " ";
  }
  cout<<endl;
}
bool find_path(){
  parent.assign(total, -1);
  index_used.assign(total, -1);
  parent[s] = s;
  queue<int> Q; Q.push(s);
  while(!Q.empty()){
    int ac = Q.front(); Q.pop();
    for(int i = 0; i<G[ac].size(); i++){
      int nxt = G[ac][i].first;
      if(parent[nxt] == -1 && G[ac][i].second > 0){
	parent[nxt] = ac;
	index_used[nxt] = i;
	Q.push(nxt);
      }
    }
  }
  return parent[t] != -1;
}
int get_flow(){
  int flow = 0;
  int ac;

  // search flow
  ac = t;
  //cout << ac << " ";
  int min_flow = 1e9;
  while(parent[ac] != ac){
    int nxt = parent[ac];
    int pos = index_used[ac];
    
    min_flow = min(min_flow, G[nxt][pos].second);

    ac = nxt;
    //cout << ac << " ";
  }
  //cout << endl;
  //cout << min_flow<<endl;
  
  // reverse
  ac = t;
  while(parent[ac] != ac){
    int nxt = parent[ac];
    int pos = index_used[ac];

    G[nxt][pos].second -= min_flow;
    G[ac][R[nxt][pos]].second += min_flow;

    ac = nxt;
  }
  return min_flow;
}

int mf(){
  int flow = 0;
  while(true){
    bool found = find_path();
    if(!found) break;
    //print_flow();
    flow += get_flow();
  }
  return flow;
}

int main(){
  cin >> n;
  
  input.assign(2*n-1, vector<char>(2*n-1));
  for(int i = 0; i<2*n-1; i++)
    for(int j = 0; j<2*n-1; j++)
      cin >> input[i][j];

  idx.assign(n+1, vector<int>(n+1));
  for(int i = 0; i<n+1; i++)
    for(int j = 0; j<n+1; j++)
      idx[i][j] = total++;
  
  s = idx[0][0], t = idx[n][n];
  G.assign(total, vector<ii>());
  R.assign(total, vector<int>());

  // gen the internal graph
  for(int row = 1; row<n; row++){
    for(int col = 1; col<n; col++){
      joinDown(row, col);
      joinRight(row, col);
    }
    joinUp(1, row);
    joinLeft(row, 1);
  }

  for(int row = 0; row<=n; row++){
    for(int col = 0; col<=n; col++){
      if(idx[row][col] == s || idx[row][col]==t) continue;
      if((row+col)%2)
	joinNodes(s, idx[row][col], 1, 0);
      else
	joinNodes(idx[row][col], t, 1, 0);
    }
  }
  //test();
  int reserved = mf();
  
  //cout << flow << endl;
  int touse = 0;
  for(int row = 1; row<n; row++){
    for(int col = 1; col<n; col++){
      if(validRight(row, col)) touse++;
      if(validDown(row,col)) touse++;
    }
    if(validLeft(row, 1)) touse++;
    if(validUp(1, row)) touse++;
  }

  //cout << touse <<endl;
  //cout << reserved <<endl;

  int ans = touse-reserved+1;
  cout << ans<<"\n";
  
}
