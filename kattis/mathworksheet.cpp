#include <bits/stdc++.h>
using namespace std;

int getNeeded(int v) {
  int ans = v < 0? 1 : 0;
  v = abs(v);
  while(v){
    ans++;
    v/=10;
  }
  return ans;
}

int getWidth(int lo, int hi) {
  int d_lo = getNeeded(lo);
  int d_hi = getNeeded(hi);
  return max(d_lo, d_hi);
}

int main(){
  int n;
  int tc = 0;
  while(scanf("%d", &n)!=EOF && n) {
    if(tc > 0) printf("\n");
    tc++;
    
    vector<int> ans;
    for(int i  =0; i<n; i++){
      int a, b; char op;
      scanf("%d %c %d", &a, &op, &b);
      if(op == '*')
	ans.push_back(a*b);
      else if(op=='-')
	ans.push_back(a-b);
      else if(op=='+')
	ans.push_back(a+b);
    }

    int lo = ans[0], hi = ans[0];
    for(int i = 0; i<n; i++){
      lo = min(lo, ans[i]);
      hi = max(hi, ans[i]);
    }

    int width = getWidth(lo,hi);
    int columns = 51/(width+1);

    char format[10];
    sprintf(format, "%%%dd", width);

    //printf("%s\n", format);

    
    int c = 0;
    for(int i = 0; i<n; i++){
      if(c>0) printf(" ");

      printf(format, ans[i]);
      c++;
      if(c==columns){
	c = 0;
	printf("\n");
      }
    }
    if(c) printf("\n");

  }
}
