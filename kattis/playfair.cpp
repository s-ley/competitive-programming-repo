#include <bits/stdc++.h>
using namespace std;
using ii = pair<int,int>;

int TEST = 0;

class Helper{
public:
  static int letterToInt(char x) {
    if('a' <= x && x <= 'z')
      return x-'a';
    if('A' <= x && x <= 'Z')
      return x-'A';
    return -1;
  }
  static char intToUpperLetter(int x) {
    return 'a'+x;
  }
  static void print(vector<int> &line) {
    for(int j = 0; j<line.size(); j++){
      cout << (char)(line[j]+'A');
    }
    cout<<endl;
  }
  static void print(vector<vector<int> > &mat){
    for(int i = 0; i<mat.size(); i++){
      Helper::print(mat[i]);
    }
  }
  static void print(ii a) {
    cout << "("<< a.first << ","<<a.second<<")";
  }
};

class Sol {
  vector<vector<int> > mat;
  string keyPhrase, plainText;
  vector<int> convertedPlainText;
  void read(){
    getline(cin, keyPhrase);
    getline(cin, plainText);
  }
  static void advance(int &x, int &y){
    x++;
    if(x>=5){
      x = 0;
      y++;
    }
  }
  void init(){
    read();
    mat.assign(5, vector<int>(5));
    int i=0,j=0;
    vector<int> used(26, 0);
    used[Helper::letterToInt('q')] = 1;
    for(int pos = 0; pos < keyPhrase.size(); pos++){
      int nxt = Helper::letterToInt(keyPhrase[pos]);
      if(nxt >= 0 && !used[nxt]){
	mat[i][j] = nxt;
	used[nxt] = 1;
	Sol::advance(i,j);
      }
    }
    for(int pos = 0; pos<26; pos++){
      if(!used[pos]){
	mat[i][j] = pos;
	used[pos] = 1;
	Sol::advance(i,j);
      }
    }
    if(TEST >= 1) {
      Helper::print(mat);
    }
    convertToIntArray();
  }
  void convertToIntArray() {
    convertedPlainText.clear();
    int xVal = Helper::letterToInt('x');
    for(int i = 0; i<plainText.size(); i++){
      int val = Helper::letterToInt(plainText[i]);
      if(val >= 0){
	if(convertedPlainText.size()%2 == 1 && convertedPlainText[convertedPlainText.size()-1] == val) {
	  convertedPlainText.push_back(xVal);
	}
	convertedPlainText.push_back(val);
      }
    }
    if(convertedPlainText.size()%2==1){
      convertedPlainText.push_back(xVal);
    }
    if(TEST >= 1) {
      Helper::print(convertedPlainText);
    }
  }
  ii search(int v) {
    for(int i = 0; i<5;i++){
      for(int j = 0; j<5; j++){
	if(mat[i][j] == v) return ii(i,j);
      }
    }
    return ii(-1,-1);
  }
  bool sameRow(ii a, ii b){
    return a.second == b.second;
  }
  bool sameCol(ii a, ii b){
    return a.first == b.first;
  }
public:
  void solve() {
    init();
    vector<int> tmp = convertedPlainText;
    for(int i = 0; i<tmp.size(); i+=2){
      ii a = search(tmp[i]);
      ii b = search(tmp[i+1]);
      if(TEST >= 2) {
	cout << "STEP "<<i/2+1<<endl;
	cout << "Original pairs ";
	Helper::print(a);Helper::print(b);
	cout <<endl;
      }
      
      if(sameRow(a,b)){
	a.first=(a.first+1+5)%5;
	b.first=(b.first+1+5)%5;
      } else if(sameCol(a,b)) {
	a.second=(a.second+1+5)%5;
	b.second=(b.second+1+5)%5;
      } else {
	int tmp = a.first;
	a.first = b.first;
	b.first = tmp;
      }
      if(TEST >= 2){
	cout << "Converted pairs ";
	Helper::print(a);Helper::print(b);
	cout <<endl;
      }
      
      tmp[i] = mat[a.first][a.second];
      tmp[i+1] = mat[b.first][b.second];
    }
    Helper::print(tmp);
  }
};

int main(){
  Sol S;
  S.solve();
}
