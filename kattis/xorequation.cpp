#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int D = 10;
const int Q = -1;
const int TEST = 0;
ll A[D], B[D], C[D];

void printArr(ll *arr){ for(int i = 0; i<D; i++) cout << arr[i] << " "; cout << endl; }

int compare(ll *a, ll *b, int &bp){
  for(int i = 0; i<D; i++){
    if(a[i] < b[i]){
      bp = i;
      return -1;
    }
    if(a[i] > b[i]){
      bp = i;
      return 1;
    }
  }
  return 0;
}
void gen(string n, ll *arr){
  int pad = D-n.size();
  for(int i = 0; i<D; i++){
    if(i<pad)
      arr[i] = 0;
    else if(n[i-pad]=='?')
      arr[i] = Q;
    else
      arr[i] = n[i-pad]-'0';
  }
}
void getDig(ll num, ll *res){
  for(int i = D-1; i>=0; i--, num/=10){
    res[i] = num%10;
  }
}
void copy(ll *orig, ll *res){for(int i  =0; i<D; i++)res[i]=orig[i];}
ll dig[D];
void addOneQ(ll *res, int bp, ll *orig){
  for(int i = bp-1; i>=0; i--){
    if(orig[i]==Q){
      res[i]++;
      if(res[i] >= 10){
	res[i] = 0;
      } else {
	break;
      }
    }
  }
}
int firstPosition(ll *arr) {
  for(int i = 0; i<D; i++)
    if(arr[i] != 0)
      return i;
  return D-1;
}

void findSmallestBig(ll num, ll *orig, ll *res) {
  copy(orig, res);
  getDig(num, dig);
  for(int i = 0; i<D; i++){
    if(res[i] == Q){
      res[i] = dig[i];
    }
  }

  int fp = firstPosition(orig);

  if(TEST >= 2)
    cout << "fp="<<fp<<endl; 
  
  if(fp != D-1 && orig[fp] == Q && res[fp] == 0)
    res[fp] = 1;
  
  int bp = Q;
  int comp = compare(res, dig, bp);
  
  if(bp != Q){
    for(int i = bp+1; i<D; i++)
      if(orig[i] == Q)
	res[i] = 0;
  }
  
  if(comp >= 0) return;

  addOneQ(res, bp, orig);
}

ll tmp[D], tmplo[D], tmphi[D];
bool inRange(ll lo, ll hi, ll *mask) {
  int bp = 0;
  findSmallestBig(lo, mask, tmp);
  getDig(lo, tmplo);
  getDig(hi, tmphi);

  if(TEST >=2 ){
    cout <<"Lo: "; printArr(tmplo);
    cout << "Hi: "; printArr(tmphi);
    cout << "lowerbound: "; printArr(tmp);
    cout << "Lo<=lb? "<< compare(tmplo, tmp, bp) << endl;
    cout << "lb<=hi? "<< compare(tmp, tmphi, bp) << endl;
  }
  
  return compare(tmplo, tmp, bp) <= 0 && compare(tmp, tmphi, bp) <= 0;
}

vector<ll> P;
void init() {
  ll pot = 1;
  ll maxP = 1e9;
  while(pot < maxP) {
    //cout << pot << " ";
    P.push_back(pot);
    pot <<= 1;
  }
  //cout <<endl;
}

ll solve(int p, ll acA, ll acB, ll acC) {
  if(p < 0) return 1;
  ll ans = 0;
  
  ll Alo, Ahi, Blo, Bhi, Clo, Chi;
  ll pp;

  pp = P[p];
  Alo = acA;
  Blo = acB+pp;
  Clo = acC+pp;
  Ahi = acA+pp-1;
  Bhi = acB+2*pp-1;
  Chi = acC+2*pp-1;
  if(inRange(Alo, Ahi, A) && inRange(Blo, Bhi, B) && inRange(Clo, Chi, C))
    ans += solve(p-1, Alo, Blo, Clo);
  
  Alo = acA+pp;
  Blo = acB;
  Ahi = acA+2*pp-1;
  Bhi = acB+pp-1;
  if(inRange(Alo, Ahi, A) && inRange(Blo, Bhi, B) && inRange(Clo, Chi, C))
    ans += solve(p-1, Alo, Blo, Clo);

  Blo = acB+pp;
  Clo = acC;
  Bhi = acB+2*pp-1;
  Chi = acC+pp-1;
  if(inRange(Alo, Ahi, A) && inRange(Blo, Bhi, B) && inRange(Clo, Chi, C))
    ans += solve(p-1, Alo, Blo, Clo);

  Alo = acA;
  Blo = acB;
  Clo = acC;
  Ahi = acA+pp-1;
  Bhi = acB+pp-1;
  Chi = acC+pp-1;
  if(inRange(Alo, Ahi, A) && inRange(Blo, Bhi, B) && inRange(Clo, Chi, C))
    ans += solve(p-1, Alo, Blo, Clo);

  return ans;
}

int main(){
  /*
  string t1; int lo, hi;
  while(cin >> t1 >> lo >> hi) {
    gen(t1, A);

    cout << "Orig: ";
    printArr(A);
    
    bool ans = inRange(lo, hi, A);

    cout << "In range ["<<lo<<","<<hi<<"]?"; 
    cout << ans << endl;
  }
  //*/
  init();
  string n1, op, n2, eq, n3;
  cin >> n1 >> op >> n2 >> eq >> n3;
  gen(n1, A);
  gen(n2, B);
  gen(n3, C);

  ll ans = solve(P.size()-1, 0, 0, 0);

  cout << ans << "\n";
  //*/
}
