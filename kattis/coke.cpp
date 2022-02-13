#include <bits/stdc++.h>
using namespace std;

const int TEST = 0;

int n, p1, p5, p10;
int from5, from10;

void print() {
  printf("n=%d, p1=%d, p5=%d, p10=%d, from5=%d, from10=%d\n", n, p1, p5, p10, from5, from10);
}

void useCoins(int m) {
  int tmp = min(p1, m);
  m -= tmp;
  p1 -= tmp;

  if(from10%1 && m > 0){
    m--;
    from10--;
  }

  tmp = min(from10, m);
  m -= tmp;
  from10 -= tmp;

  tmp = min(from5, m);
  m -= tmp;
  from5 -= tmp;
}

int main(){
  int tc;
  cin >> tc;
  while(tc--){
    cin >> n >> p1 >> p5 >> p10;
    from5 = 0; from10 = 0;
    if(TEST) print();

    int ans = 0;

    while(n > 0 && p10 > 0) {
      ans++; n--; p10--;
      from10 += 2;
    }
    if(TEST) print();
    while(n > 0 && p5 > 1) {
      ans += 2; n--; p5 -= 2;
      from5 += 2;
    }
    if(TEST) print();
    if(p5==1 && n>0) {
      ans += 4; n--; p5 -= 1;
      useCoins(3);
    }
    if(TEST) print();
    while(n > 0 && from5 > 1){
      ans += 6; n--; from5 -= 2;
      useCoins(6);
    }
    if(TEST) print();
    while(n > 0 && from10 > 1){
      ans += 7; n--; from10 -= 2;
      useCoins(6);
    }
    if(TEST) print();
    while(n > 0) {
      ans += 8; n--;
      useCoins(8);
    }
    if(TEST) print();

    cout << ans << endl;
  }
}
