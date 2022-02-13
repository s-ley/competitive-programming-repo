#include <bits/stdc++.h>
using namespace std;
using ii = pair<int, int>;

const int TEST = 3;

class Shuffler {
public:
  static int nextVal(int x, int sz) {
    int extra = (x&1)? sz>>1 : 0;
    return (x>>1)|extra;
  }
  static int prevVal(int x, int sz) {
    int extra = ((sz>>1)&x)? 1 : 0;
    return ((x<<1)&(sz-1))|extra;
  }
  static void nextShuffle(vector<int> &arr, int st, int ed, bool forward) {
    int sz = ed-st;
    vector<int> res(sz);
    for(int i = 0; i<sz; i++){
      int idx = forward? Shuffler::nextVal(i,sz) : Shuffler::prevVal(i,sz);
      if(TEST >= 3) {
	printf("st=%d, ed=%d, i=%d, nxt=%d\n", st, ed, i, idx);
      }
      res[idx] = arr[st+i];
    }
    for(int i = 0; i<sz; i++){
      arr[st+i] = res[i];
    }
  }
};

class Helper {
public:
  static void print(vector<int> &arr){
    for(int i = 0; i<arr.size(); i++) printf("%d ", arr[i]); printf("\n");
  }
  static void print(vector<ii> &arr){
    for(int i = 0; i<arr.size(); i++) printf("(%d,%d) ", arr[i].first, arr[i].second); printf("\n");
  }
};

class Sol {
private:
  vector<vector<ii> > S;
  void addToS(vector<int> &arr) {
    vector<ii> nxt;
    for(int i = 0; i<arr.size(); i+=2) nxt.push_back(ii(arr[i], arr[i+1]));
    S.push_back(nxt);
  }
public:
  void solve(int n){
    int sz = 1<<n;
    vector<int> arr(sz);
    for(int i = 0; i<sz; i++) arr[i] = i;

    addToS(arr);
    
    int parts = 1;
    for(int i = 1; i<n; i++) {
      int pSize = sz/parts;
      for(int j = 0; j<parts; j++){
	int st = pSize*j, ed = pSize*(j+1);
	Shuffler::nextShuffle(arr, st, ed, true);
      }
      addToS(arr);
      if(TEST) {
	printf("i=%d\n", i);
	Helper::print(arr);
      }
      parts++;
    }
    parts--;
    for(int i = 1; i<n; i++) {
      int pSize = sz/parts;
      for(int j = 0; j<parts; j++){
	int st = pSize*j, ed = pSize*(j+1);
	Shuffler::nextShuffle(arr, st, ed, false);
      }
      addToS(arr);
      if(TEST) {
	printf("i=%d\n", i);
	Helper::print(arr);
      }
      parts--;
    }

    if(TEST) {
      printf("Relations:\n");
      for(int i = 0; i<S.size(); i++){
	Helper::print(S[i]);
      }
    }
    
  }
};

int main() {
  Sol S;
  S.solve(4);
}
