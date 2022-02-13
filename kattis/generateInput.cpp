 #include <bits/stdc++.h>
using namespace std;

void babynames(){
  for(char a1 = 'A'; a1<='Z'; a1++)
      for(char a2 = 'A'; a2<='Z'; a2++)
	  for(char a3 = 'A'; a3<='Z'; a3++)
	    cout << "1 "<<a1<<a2<<a3<<" 1\n";

  cout << "3 A Z 1\n";
  cout << "3 B Y 1\n";
  cout << "3 AAA AAA 0\n";

    for(char a1 = 'A'; a1<='Z'; a1++)
      for(char a2 = 'A'; a2<='Z'; a2++)
	  for(char a3 = 'A'; a3<='Z'; a3++)
	    cout << "2 "<<a1<<a2<<a3<<"\n";

  
}

int main(){
  babynames();
}
