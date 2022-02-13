#include <bits/stdc++.h>
using namespace std;
using ll = long long;


ll phi(ll n) {
    ll result = n;
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0)
                n /= i;
            result -= result / i;
        }
    }
    if (n > 1)
        result -= result / n;
    //cout << result<<endl;
    return result;
}

ll pot(ll a, ll p, ll m){
  if(p==0) return 1;
  if(p==1) return a%m;
  ll mid = pot(a, p/2, m);
  ll ans = (mid*mid)%m;
  if(p%2)
    ans = (ans*a)%m;
  return ans;
}

ll inv(ll a, ll m){
  return pot(a, phi(m)-1, m);
}

int main(){
  int t; cin >> t;
  while(t--){
    ll a, p_1, b, p_2; cin >> a >> p_1 >> b >> p_2;
    // CRT: x ~ (u_0 + u_1*p_1)%(p_1*p_2)
    // x%p_1 ~ a ~ u_0 % p_1
    // x%p_2 ~ b ~ (u_0 + u_1*p_1)%p_2
    // (b-u_0)%p_2 ~ (u_1*p_1)%p_2
    // ((b-u_0)*p_1^{-1})%p_2 ~ u_1
    ll u_0 = a;
    ll u_1 = (b-u_0+p_2*u_0)%p_2; u_1 = (u_1*inv(p_1, p_2))%p_2;
    ll k = (p_1*p_2);
    ll x = (u_0 + u_1*p_1)%k;
    cout << x << " " << k << "\n";
  }
}
