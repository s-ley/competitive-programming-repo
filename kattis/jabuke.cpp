#include <bits/stdc++.h>
using namespace std;
using ii = pair<int, int>;

double area(ii a, ii b, ii c){
  return abs(a.first*(b.second-c.second)
	     +b.first*(c.second-a.second)
	     +c.first*(a.second-b.second))/2.0;
}

int ccw(ii a, ii b, ii c) {
  // a.x a.y 1
  // b.x b.y 1
  // c.x c.y 1
  int pos = a.first*b.second+b.first*c.second+c.first*a.second;
  int neg = -a.first*c.second-b.first*a.second-c.first*b.second;
  return pos+neg;
}

int main(){
  ii p1, p2, p3;
  cin >> p1.first >> p1.second;
  cin >> p2.first >> p2.second;
  cin >> p3.first >> p3.second;

  if(ccw(p1,p2,p3) <= 0) {
    ii tmp = p2;
    p2 = p3;
    p3 = tmp;
  }

  int n; cin >> n;

  int ans = 0;
  for(int i = 0; i<n; i++){
    ii nxt; cin >> nxt.first >> nxt.second;
    if(ccw(p1, p2, nxt) >= 0 && ccw(p2, p3, nxt) >= 0 && ccw(p3, p1, nxt) >= 0){
      ans++;
    }
  }
  double a = area(p1, p2, p3);
  cout << fixed << setprecision(1) << a <<endl;
  cout << ans << endl;
}
