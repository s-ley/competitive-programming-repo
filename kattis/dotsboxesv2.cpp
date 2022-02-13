#include <bits/stdc++.h>
using namespace std;

bool TEST = false;
void test();
void print_point(int x, int y){
  cout << "("<<x<<","<<y<<")";
}

// vars
int n;
vector<vector<char> > ascii;
int nodes;
vector<vector<int> > idx;
int s, t;
vector<vector<int> > G, W, R;

// input
void read(){
  cin >> n;
  ascii.assign(2*n-1, vector<char>(2*n-1, '.'));
  for(int i = 0; i <2*n-1; i++)
    for(int j = 0; j < 2*n-1; j++)
      cin >> ascii[i][j];
}

// check adyacency
const int UP = 1, DOWN = 2, LEFT = 3, RIGHT = 4;
bool isFree(int row, int col, int direction){
  int y = 2*row-1, x = 2*col-1;
  switch(direction){
  case UP:
    y--;
    break;
  case DOWN:
    y++;
    break;
  case LEFT:
    x--;
    break;
  case RIGHT:
    x++;
    break;
  }
  if(TEST){
    cout << "Checking direction "<< direction <<": idx="<<idx[row][col]<<" ";
    print_point(row,col);
    cout << " => ";
    print_point(x,y);
    cout << ascii[y][x];
    if(ascii[y][x]=='.')
      cout << " YES";
    else
      cout << " NO";
    cout <<endl;
  }
  return ascii[y][x] == '.';
}
int getFreeLines(){
  int ans = 0;
  for(int row = 1; row<n; row++){
    if(isFree(row,1,LEFT)) ans++;
    if(isFree(1,row,UP)) ans++;
    for(int col = 1; col<n; col++){
      if(isFree(row,col,DOWN)) ans++;
      if(isFree(row,col,RIGHT)) ans++;
    }
  }
  return ans;
}

// graph
void addEdge(int st, int ed, int w1, int w2){
  int pos_st = G[st].size();
  int pos_ed = G[ed].size();

  G[st].push_back(ed);
  G[ed].push_back(st);
  R[st].push_back(pos_ed);
  R[ed].push_back(pos_st);
  W[st].push_back(w1);
  W[ed].push_back(w2);
  if(TEST){
    cout << "Join nodes: "<<st<<" "<<ed<<endl;
  }
}
void genFlowGraph(){
  idx.assign(n+1, vector<int>(n+1, 0));
  nodes = 0;
  for(int i = 0; i<=n; i++)
    for(int j = 0; j<=n; j++)
      idx[i][j] = nodes++;

  G.assign(nodes, vector<int>());
  W.assign(nodes, vector<int>());
  R.assign(nodes, vector<int>());

  s = idx[0][0];
  t = idx[n][n];
  for(int row = 1; row<n; row++)
    for(int col = 1; col<n; col++){
      if((row+col)%2){
	addEdge(s, idx[row][col], 1, 0);
	if(row+1<n && isFree(row,col,DOWN)){
	  addEdge(idx[row][col], idx[row+1][col], 1, 0);
	}
	if(col+1<n && isFree(row,col,RIGHT)){
	  addEdge(idx[row][col], idx[row][col+1], 1, 0);
	}
	if(row-1>0 && isFree(row,col,UP)){
	  addEdge(idx[row][col], idx[row-1][col], 1, 0);
	}
	if(col-1>0 && isFree(row,col,LEFT)){
	  addEdge(idx[row][col], idx[row][col-1], 1, 0);
	}

      }else
	addEdge(idx[row][col], t, 1, 0);
    }
}

// max flow
vector<int> parent, posFound;
bool findFlow(){
  parent.assign(nodes, -1);
  posFound.assign(nodes, -1);
  parent[s] = s;
  queue<int> Q;Q.push(s);
  while(!Q.empty()){
    int ac = Q.front(); Q.pop();
    for(int i = 0; i<G[ac].size(); i++){
      int nxt = G[ac][i];
      if(W[ac][i] > 0 && parent[nxt] == -1){
	parent[nxt] = ac;
	posFound[nxt] = i;
	Q.push(nxt);
      }
    }
  }
  return parent[t] != -1;
}
int getFlow(){
  int flow = 1e9;
  int ac = t;
  int p;
  if(TEST) cout << "FLOW: ";
  while(parent[ac] != ac){
    if(TEST) cout<< ac<<" ";
    p = parent[ac];
    flow = min(flow, W[p][posFound[ac]]);
    ac = p;
  }
  if(TEST) cout << endl;
  // update
  ac = t;
  while(parent[ac] != ac){
    p = parent[ac];

    W[p][posFound[ac]] -= flow;
    W[ac][R[p][posFound[ac]]] += flow;
      
    ac = p;
  }
  return flow;
}
int mf(){
  int flow = 0;
  while(true) {
    bool found = findFlow();
    if(!found) break;
    flow += getFlow();
  }
  return flow;
}


void test(){
  cout << n << endl;
  for(int i = 0; i<ascii.size(); i++){
    for(int j = 0; j<ascii[i].size(); j++)
      cout << ascii[i][j]<<" ";
    cout << endl;
  }
  for(int i = 0; i<=n; i++){
    for(int j = 0; j<=n; j++)
      cout << idx[i][j]<<" ";
    cout<<endl;
  }
  for(int i = 0; i<nodes; i++){
    cout << i << ": ";
    for(int j = 0; j<G[i].size(); j++){
      cout << "(n="<<G[i][j]<<",w="<<W[i][j]<<",r="<<R[i][j]<<") ";
    }
    cout<<endl;
  }
  cout << "s="<<s<<" t="<<t<<endl;
}



int main(){
  read();
  genFlowGraph();
  int touse = getFreeLines();
  if(TEST){
    cout << "Spots to add lines: ";
    cout << touse<<endl;
  }

  int flow = mf();
  int reserved = (n-1)*(n-1) - flow;
  int ans = touse - reserved + 1;

  //test();

  if(TEST){
    cout << "maxflow: " << flow << endl;
    cout << "reserved: "<<reserved << endl; 
  }

  cout << ans << endl;
}
