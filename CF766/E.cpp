#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using dl = pair<int, ll>;

const int TEST = 0;
const ll INF = 1e18;

class Lad {
public:
  int f1,r1,f2,r2;
  ll w;
  void print(){
    printf("f1=%d,r1=%d,f2=%d,r2=%d,w=%lld\n",f1,r1,f2,r2,w);
  }
};

int n, m, k;
vector<ll> Move;
vector<set<int> > R;
vector<vector<dl> > F;
vector<vector<Lad> > inp;

void test() {
  cout << "Building:\n";
  for(int i = 0; i<n; i++){
    for(int j = 0; j<F[i].size(); j++){
      dl nxt = F[i][j];
      if(nxt.second < INF)
	printf("%5d,%lld ", nxt.first, nxt.second);
      else
	printf("%5d,X ", nxt.first);
    }
    printf("\n");
  }
}

void propagate(int f, int p) {
  dl ac = F[f][p];
  for(int inc = -1; inc<=1; inc+=2){
    for(int i = p+inc; 0 <= i && i < F[f].size(); i+=inc){
      dl nxt = F[f][i];
      ll nw = ac.second + abs(ac.first - nxt.first)*Move[f];
      if(nw < nxt.second)
	F[f][i].second = nw;
      else
	break;
    }
  }
}

void doFloor(int f){
  for(int i = 0; i<F[f].size(); i++){
    dl ac = F[f][i];
    if(ac.second < INF)
      propagate(f, i);
  }
}

int getPos(int f, int r) {
  vector<dl>::iterator it = lower_bound(F[f].begin(), F[f].end(), dl(r, -INF));
  return (it-F[f].begin());
}

int main(){
  int t; cin >> t;
  while(t--){
    // Init
    cin >> n >> m >> k;

    inp.assign(n, vector<Lad>());
    R.assign(n, set<int>());

    // Read
    Move.resize(n);
    for(int i = 0; i<n; i++) cin >> Move[i];

    if(TEST)
      printf("Read ladders:\n");

    for(int i = 0; i<k; i++){
      Lad ac;
      cin >> ac.f1 >> ac.r1 >> ac.f2 >> ac.r2 >> ac.w;
      ac.f1--;ac.r1--;ac.f2--;ac.r2--;
      if(TEST){
	ac.print();
      }
      inp[ac.f1].push_back(ac);
      R[ac.f1].insert(ac.r1);
      R[ac.f2].insert(ac.r2);
    }

    if(TEST)
      printf("Add extra:\n");

    R[0].insert(0);
    R[n-1].insert(m-1);

    if(TEST)
      printf("Save (room,distance)\n");
    
    // Save (room,distance)
    F.assign(n, vector<dl>());
    for(int i = 0; i<n; i++){
      for(auto &x : R[i]){
	F[i].push_back(dl(x, INF));
      }
    }

    F[0][0].second = 0;

    for(int f = 0; f<n; f++){
      doFloor(f);

      for(int i = 0; i<inp[f].size(); i++){
	Lad ac = inp[f][i];

	int p1 = getPos(f,ac.r1);
	int p2 = getPos(ac.f2, ac.r2);

	ll w2 = F[f][p1].second - ac.w;

	if(F[f][p1].second < INF)
	  F[ac.f2][p2].second = min(F[ac.f2][p2].second, w2);
      }

      if(TEST)
	test();
    }

    int sz = F[n-1].size();
    if(F[n-1][sz-1].second < INF)
      cout << F[n-1][sz-1].second << "\n";
    else
      cout << "NO ESCAPE\n";
  }
}
