#include <bits/stdc++.h>
using namespace std;

const int LS = 'z'-'a'+2;
const int MAX = LS*LS*LS + LS*LS + LS + 5;

const int TEST = 0;

int toInt(char x) { return x-'a'+1; }
int toInt(string s) {
  int v = 0;
  int pos = s.size()-1;
  int pot = 1;
  while(pos>=0){
    v += toInt(s[pos])*pot;
    pos--;
    pot *= LS;
  }
  return v;
}

bool appearsAfter(vector<vector<int> > &pos, int st, int val) {
  return pos[val].size() > 0 && pos[val][pos[val].size()-1] > st;
}

int main(){
  if(TEST) {
    cout << "LS=" << LS  << endl;
  }
  int t; cin >> t;
  while(t--){
    int n; cin >> n;
    vector<string> inp;
    
    bool ok = false;
    vector<vector<int> > pos(MAX, vector<int>());
    
    for(int i = 0; i<n; i++){
      string str;
      cin >> str;
      inp.push_back(str);

      bool palin = str.size() == 1 ||
	(str.size() > 1 && str[0] == str[str.size()-1]);
      
      if(palin)
	ok = true;
      else
	pos[toInt(str)].push_back(i);
    }

    for(int i = 0; i<n && !ok; i++){
      string ac = inp[i];
      int sz = ac.size();
      int val = toInt(ac);
      if(TEST) {
	printf("s=%s,sz=%d,v=%d\n",ac.c_str(),sz,val);
      }
      if(sz == 2) {
	// search it backwards
	string rev=""; rev += ac[1]; rev += ac[0];
	int rVal = toInt(rev);
	if(TEST) {
	  printf("rev=%s,v=%d\n",rev.c_str(),rVal);
	}
	if(appearsAfter(pos,i,rVal)) // appears after
	  ok = true;

	// search one of 3
	for(char x = 'a'; x<='z' && !ok; x++){
	  string nxt=""; nxt += x; nxt += rev;
	  rVal = toInt(nxt);
	  
	  if(appearsAfter(pos,i,rVal)) // appears after
	    ok = true;
	}
      } else if(sz == 3) {
	// search first 2 backwards
	string rev1 = ""; rev1 +=  ac[1]; rev1 += ac[0];
	int rVal = toInt(rev1);
	if(appearsAfter(pos,i,rVal)) // appears after
	  ok = true;

	// search first 3 backwards
	string rev2 = ""; rev2 +=  ac[2]; rev2 += rev1;
	rVal = toInt(rev2);
	if(appearsAfter(pos,i,rVal)) // appears after
	  ok = true;
      }
    }

    if(ok){
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
  }
}
