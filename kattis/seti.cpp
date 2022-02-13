#include <bits/stdc++.h>
using namespace std;

int TEST = 0;

class Helper {
public:
  static void print(vector<vector<int> > X){
    for(int i =0; i<X.size(); i++) Helper::print(X[i]);
  }
  static void print(vector<int> vals) {
    if(vals.size() == 0) return;
    cout << vals[0];
    for(int i = 1; i<vals.size(); i++) cout << " " << vals[i];
    cout << endl;
  }
  static int charToInt(char x) {
    if(x=='*') return 0;
    return x-'a'+1;
  }
  static vector<int> stringToInt(string s) {
    vector<int> ans;
    for(int i = 0; i<s.size(); i++) ans.push_back(charToInt(s[i]));
    return ans;
  }
  static int pow(int a, int x, int mod) {
    if(x == 0) return 1;
    if(x == 1) return a;
    int tmp = Helper::pow(a, x/2, mod);
    tmp = (tmp*tmp)%mod;
    if(x&1) {
      return (tmp*a)%mod;
    }
    return tmp;
  }
};

class Sol {
private:
  vector<vector<int> > A;
  vector<int> inverses;
  int n;
  int mod;
  void init(int p, string str) {
    n = str.size();
    mod = p;
    
    // Init mat
    A.assign(n, vector<int>(n+1));
    vector<int> results = Helper::stringToInt(str);
    for(int i = 0; i<n; i++){
      int k = 1;
      for(int j = 0; j<n; j++){
	A[i][j] = k;
	k = (k*(i+1))%mod;
      }
    }
    for(int i = 0; i<n; i++) {
      A[i][n] = results[i];
    }

    // Init inverses
    inverses.assign(mod, 1);
    for(int i = 2; i<mod; i++){
      inverses[i] = Helper::pow(i, mod-2, mod);
    }
  }

  void swapRows(int a, int b) {
    for(int i = 0; i<=n; i++){
      swap(A[a][i], A[b][i]);
    }
  }
  bool moveNonZeroColToRow(int rowCol) {
    int row = rowCol;
    for(; row<n; row++){
      if(A[row][rowCol] != 0) break;
    }
    if(row == n) return true;
    if(rowCol != row){
      swapRows(rowCol, row);
    }
    return false;
  }
  void multiplyRow(int row, int val) {
    for(int i = 0; i<=n; i++) {
      A[row][i] = (A[row][i]*val)%mod;
    }
  }
  void substractRowToRowXTimes(int orig, int dest, int x) {
    for(int i = 0; i<=n; i++){
      A[dest][i] = (A[dest][i] - x * A[orig][i] + x * mod)%mod;
    }
  }
public:
  void solve(int p, string str) {
    init(p, str);
    if(TEST > 0){
      cout << "Init mat"<<endl;
      Helper::print(A);
      cout << "inverses"<<endl;
      Helper::print(inverses);
    }

    for(int i = 0; i<n; i++){
      if(TEST > 1){
	cout << "Step "<<i<<endl;
      }
      bool isEmpty = moveNonZeroColToRow(i);
      if(TEST > 1) {
	cout << "Moved non zero:"<<endl;
	Helper::print(A);
      }
      if(!isEmpty) {
	multiplyRow(i, inverses[A[i][i]]);

	if(TEST > 1){
	  cout << "Normalized:"<<endl;
	  Helper::print(A);
	}
	
	for(int j = 0; j<n; j++){
	  if(j == i) continue;
	  substractRowToRowXTimes(i, j, A[j][i]);

	  if(TEST > 2) {
	    cout << "cero-ed:"<<endl;
	    Helper::print(A);
	  }
	}
      }
    }

    if(TEST > 0){
      cout << "Result"<<endl;
      Helper::print(A);
    }

    for(int i = 0; i<n; i++) {
      if(i > 0) cout << " ";
      cout << A[i][n];
    }
    cout << endl;
  }
};



int main(){
  int tc; cin >> tc;

  Sol S;
  while(tc--){
    int p; string str;
    cin >> p >> str;
    if(TEST > 0){
      cout << "INPUT: "<<endl;
      cout << p << " " << str<<endl;
    }
    
    S.solve(p, str);
  }
}
