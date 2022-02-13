#include <bits/stdc++.h>
using namespace std;
int n, m;
vector<vector<int> > P;

vector<int> I;
vector<vector<int> > C;

int getC(int p, int t) {
  if(t<=0) return 0;

  return C[p][t%(P[p][4]+1)];
}
void setC(int p, int t, int v) {
  C[p][t%(P[p][4]+1)] = v;
}

int main(){
  cin >> n >> m;
  P.assign(n, vector<int>(6, 0));
  for(int i = 0; i<n; i++)
    for(int j = 0; j<6; j++)
      cin >> P[i][j];

  I.assign(n, 0);
  C.resize(n);
  for(int i = 0; i<n; i++){
    C[i] = vector<int>(P[i][4]+1, 0);
    for(int j = 1; j<=P[i][4]; j++){
      C[i][j] = min(getC(i, j-P[i][2])+P[i][3], getC(i, j-P[i][4])+P[i][5]);
    }
    I[i] = P[i][4];
  }

  int servings = 0;
  while(true) {
    servings++;
    int cost = 0;
    for(int i = 0; i<n; i++){
      int missing = P[i][0]*servings-P[i][1];
      while(missing > I[i]) {
	I[i]++;
	int nxt = min(getC(i, I[i]-P[i][2])+P[i][3], getC(i, I[i]-P[i][4])+P[i][5]);
	setC(i, I[i], nxt);
      }
      cost += getC(i, I[i]);
    }
    if(cost > m) break;
  }
  cout << servings-1 << endl;
}
