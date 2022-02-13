#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/trie_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

typedef tree<
  string,
  null_type,
  less<string>,
  rb_tree_tag,
  tree_order_statistics_node_update>
OST;

int main(){
  OST roots[3];
  roots[1] = OST();
  roots[2] = OST();
  
  ios::sync_with_stdio(0);
  int op;
  while(cin >> op && op){
    if(op == 1){
      string name; int gender;
      cin >> name >> gender;
      roots[gender].insert(name);
    } else if(op == 2){
      string name; cin >> name;
      roots[1].erase(name);
      roots[2].erase(name);
    } else {
      string st, ed; int gender;
      cin >> st >> ed >> gender;
      int ans = 0;
      if(gender == 1 || gender == 0)
	ans += (roots[1].order_of_key(ed)-roots[1].order_of_key(st));
      if(gender == 2 || gender == 0)
	ans += (roots[2].order_of_key(ed)-roots[2].order_of_key(st));
      cout << ans << "\n";
    }
  }
}
