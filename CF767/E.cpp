#include <bits/stdc++.h>
using namespace std;

vector<vector<int> > mat;
int n;

const int UP=1,DOWN=2,LEFT=3,RIGHT=4;
const int TEST = 0;


bool valid(int x){ return 0 <= x && x < n; }

int getHLine(int x1, int x2, int y) {
  int ans = 0;
  for(int i = x1; i<= x2; i+= 4){
    ans = ans^mat[i][y]^mat[i+1][y];
    if(TEST) {
      printf("Used mat[%d][%d]=%d\n",i,y,mat[i][y]);
      printf("Used mat[%d][%d]=%d\n",i+1,y,mat[i+1][y]);
    }
  }
  return ans;
}
int getVLine(int x, int y1, int y2) {
  int ans = 0;
  for(int i = y1; i<=y2; i+= 4){
    ans = ans^mat[x][i]^mat[x][i+1];
    if(TEST) {
      printf("Used mat[%d][%d]=%d\n",x,i,mat[x][i]);
      printf("Used mat[%d][%d]=%d\n",x,i+1,mat[x][i+1]);
    }
  }
  return ans;
}

int getVT(int x1, int x2, int y, int dir) {
  if(TEST) {
    printf("dir=%d,line=%d\n",dir,y);
  }
  
  int ans = 0;
  while(valid(y)) {
    if(TEST) {
      printf("line=%d\n",y);
    }
    ans = ans^getHLine(x1,x2,y);
    x1 -= 2;
    x2 += 2;
    if(dir == UP)
      y -= 2;
    else
      y += 2;
  }
  return ans;
}
int getHT(int x, int y1, int y2, int dir) {
  int ans = 0;
  while(valid(x)){
    if(TEST) {
      printf("line=%d\n",x);
    }

    ans = ans^getVLine(x,y1,y2);
    y1 -= 2; y2 += 2;
    if(dir == LEFT)
      x -= 2;
    else
      x += 2;
  }
  return ans;
}

int solveM4() {
  int ans = 0;
  // T1 \/
  int x1 = n/2-2;
  ans = ans^getVT(x1, x1+1, x1, UP);
  // T2 <
  ans = ans^getHT(x1+3, x1+1,x1+2, RIGHT);
  // T3
  ans = ans^(getVT(x1, x1+1, x1+3, DOWN));
  // T4 >
  if(n > 4)
    ans = ans^getHT(x1-2, x1+1, x1+2, LEFT);

  return ans;
}
int solveM2() {
  int ans = 0;
  int b = (n/4)*2;
  // T1 \/
  ans = ans^getVT(b, b+1, b, UP);
  if(n > 2){
    // T2 <
    ans = ans^getHT(b+3, b+1,b+2, RIGHT);
    // T3
    ans = ans^getVT(b, b+1, b+3, DOWN);
    // T4 >
    ans = ans^getHT(b-2, b+1, b+2, LEFT);
  }
  return ans;
}

int main(){
  int t; cin >> t;
  while(t--){
    cin >> n;
    mat.assign(n, vector<int>(n));
    for(int i = 0; i<n; i++)
      for(int j = 0; j<n; j++)
	cin >> mat[i][j];

    int ans;
    if(n%4==0){
      ans = solveM4();
    } else {
      ans = solveM2();
    }
    cout << ans<<endl;
  }
  

}
