#include <bits/stdc++.h>
using namespace std;
using ll = unsigned long long;

const ll MAX = 1ULL<<63;

vector<ll> primes = {2,3,5,7,9,11,13,17,19,23,25,29,31,37,41,43};

bool mult(ll a, ll b){
  return MAX%b? a <= MAX/b : a<MAX/b;
}

map<ll, ll> ans;

struct S {
  vector<int> ac;
  ll sum, comb, val;

  void initSum(){
    sum = 0;
    for(int i = 0; i<ac.size(); i++)
      sum += ac[i];
  }
  bool initVal(){
    val = 1;
    for(int i = 0; i<val.size(); i++){
      for(int j = 1; j<=ac[i]; j++){
	if(mult(val, primes[i]))
	  val *= primes[i];
	else
	  return false;
      }
    }
    return true;
  }
};

void init(){
  ans[1] = 2;

  S st;
  st.ac = {1,1};

  
  vector<int> ac = {1,1};
  
  ll comb = 2;
  ll val = 6;
  
}

ll solve(ll n){
  if(n == 1) return 2;
  return 1;
}

int main(){
  cout << primes.size() << endl;
  
}
