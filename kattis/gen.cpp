#include <bits/stdc++.h>
using namespace std;
using ii = pair<int, int>;
using di = pair<ii, ii>;

int main(){
  int C = 150, p1=500,p5=100,p10=50;


  vector<di> testcases;

  int maxAmount = 1e5;
  for(int i = 1; i<= C && testcases.size() < maxAmount; i++){
    for(int j = 1; j <= p1 && testcases.size() < maxAmount; j++){
      for(int k = 1; k<=p5 && testcases.size() < maxAmount; k++){
	for(int l = 1; l<=p10 && testcases.size() < maxAmount; l++){
	  if(C*8 <= p1+p5*5+p10*10) {
	    testcases.push_back(di(ii(i,j),ii(k,l)));
	  }
	}
      }
    }
  }

  cout << testcases.size() << endl;
  for(int i = 0; i<testcases.size(); i++){
    cout << testcases[i].first.first << " " << testcases[i].first.second << " " << testcases[i].second.first << " "<<testcases[i].second.second<<endl;
  }
}
