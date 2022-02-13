#include <bits/stdc++.h>
using namespace std;

const int SZ = 'Z'-'A'+1;
int toInt(char x){ return x-'A'; }

struct Node {
  vector<Node *> children;
  int total;
  int ending;
  Node(){
    ending = 0;
    total = 0;
    children.assign(SZ, NULL);
  }
  Node* getChild(char x){
    int pos = toInt(x);
    if(children[pos] == NULL)
      children[pos] = new Node();
    return children[pos];
  }
};
bool exists(string &str, Node *T){
  for(int i = 0; i<str.size(); i++){
    T = T->getChild(str[i]);
  }
  return T->ending;
}
void add(string &str, Node *T){
  for(int i = 0; i<str.size(); i++){
    T = T->getChild(str[i]);
    T->total++;
  }
  T->ending = 1;
}
void remove(string &str, Node *T){
  for(int i = 0; i<str.size(); i++){
    T = T->getChild(str[i]);
    T->total--;
  }
  T->ending = 0;
}
int countLess(string &str, Node *T){
  int total = 0;
  for(int i = 0; i<str.size(); i++){
    for(char x = 'A'; x<str[i]; x++){
      Node* less = T->getChild(x);
      total += less->total;
    }
    T = T->getChild(str[i]);
  }
  return total;
}


int main(){
  Node* roots[3];
  roots[1] = new Node();
  roots[2] = new Node();
  int op;
  ios::sync_with_stdio(0);
  while(cin >> op && op){
    if(op == 1){
      string name; int gender;
      cin >> name >> gender;
      add(name, roots[gender]);
    } else if(op == 2){
      string name; cin >> name;
      if(exists(name, roots[1]))
	remove(name, roots[1]);
      if(exists(name, roots[2]))
	remove(name, roots[2]);
    } else {
      string st, ed; int gender;
      cin >> st >> ed >> gender;
      int ans = 0;
      if(gender == 1 || gender == 0)
	ans += countLess(ed, roots[1]) - countLess(st, roots[1]);
      if(gender == 2 || gender == 0)
	ans += countLess(ed, roots[2]) - countLess(st, roots[2]);
      cout << ans << "\n";
    }
  }
}
