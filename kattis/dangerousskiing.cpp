#include <bits/stdc++.h>
using namespace std;

bool TEST = false;

const int N = 300;
double DP[N][N];
double P[N][N];
int n, m;
void init(){
  for(int i = 0; i<N; i++){
    for(int j  = 0; j<N; j++){
      DP[i][j] = -2;
      P[i][j] = -2;
    }
    DP[i][0] = 1; // With i walks left, you can reach node 0 with prob 1
  }
}
void test(){
  for(int i = 0; i<n; i++){
    for(int j = 0; j<n; j++)
      cout << P[i][j]<<" ";
    cout <<endl;
  }
}

void read(){
  scanf("%d %d", &n, &m);
  for(int i = 0; i<m; i++){
    int a, b; double w;
    scanf("%d %d %lf", &a, &b, &w);
    if(a==b) continue;
    int st = min(a,b), ed = max(a,b);
    P[st][ed] = 1-w;
  }
}

double f(int walks, int node) { // what p can you reach the node with that amount of walks
  if(TEST)
    cout << "f-"<<walks<<" "<<node<<endl;
  if(walks < 0) return -1;
  if(DP[walks][node] != -2) return DP[walks][node];

  double best = -1;
  for(int i = 0; i<n; i++){
    if(P[i][node] != -2 && i < node){
      double p1 = f(walks, i);
      double p2 = f(walks-1, i);

      if(p1 >= 0)
	best = max(best, p1*P[i][node]);
      if(p2 >= 0)
	best = max(best, p2);
      
      if(TEST){
	cout << "node: "<< node << endl;
	cout << "walks: "<<walks<<endl;
	cout << "to node: "<<i<<endl;
	cout << "probs: "<<p1 << " " << p2<<endl;
      }

    } else if(P[node][i] != 2 && node < i){
      double p = f(walks-1, i);
      if(TEST){
	cout << "node: " << node << endl;
	cout << "walks: "<<walks<<endl;
	cout << "to node: "<<i<<endl;
	cout << "prob: "<< p<<endl;
      }
      best = max(p, best);
    }
  }

  DP[walks][node] = best;
  return best;
}

int main(){
  init();
  read();
  double best = -1;
  for(int i = 0; i<n; i++){
    if(i>0) printf(" ");
    best = max(f(i, n-1), best);
    if(best == -1)
      printf("-1");
    else
      printf("%1.9lf", best);
  }
  printf("\n");

  if(TEST){
    for(int i = 0; i<n; i++){
      for(int j = 0; j<n; j++){
	cout << DP[i][j] << " ";
      }
      cout <<endl;
    }
    test();
  }
}
