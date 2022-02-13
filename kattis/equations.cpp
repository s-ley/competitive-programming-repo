#include <bits/stdc++.h>
using namespace std;
using ii = pair<int,int>;

const int TEST = 0;

const int XS = 3;
const int YS = 4;
const int CS = 5;
const int HAS_X = 1;
const int HAS_Y = 2;
const int IS_COMPOUND=6;
const int IS_NONE=7;

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

class Term {
public:
  int type;
  int amount;
  void parse(string str) {
    int sz = str.size();
    if(str[sz-1] == 'x')
      type = XS;
    else if(str[sz-1] == 'y')
      type = YS;
    else {
      type = CS;
      stringstream ss(str);
      ss >> amount;
      return;
    }
    if(sz == 2 && str[0]=='-'){
      amount = -1;
      return;
    } else if(sz == 1) {
      amount = 1;
      return;
    }
    stringstream ss(str);
    ss >> amount;
  }
  void print() {
    char type = XS? 'x' : (YS? 'y' : ' ');
    printf("%d%c", amount, type);
  }
};

/* Saved as Ay+Bx+C=0 */
class Eq {
public:
  int xs,ys,cs;
  void parse(string str) {
    xs = ys = cs = 0;
    stringstream ss(str);

    bool isTerm=true, isAdd=true, isLeft=true;
    string ac;
    while(ss >> ac) {
      // Logic for non-terms
      if(!isTerm){
	isTerm = true;
	switch(ac[0]) {
	case '-':
	  isAdd=false;
	  break;
	case '+':
	  isAdd=true;
	  break;
	case '=':
	  isAdd=true;
	  isLeft=false;
	}
	continue;
      }
      // Parse term
      Term t;
      t.parse(ac);
      if(!isAdd) t.amount *= -1;

      // Add it to total
      int val = t.amount;
      if(!isLeft) val *= -1;
      switch(t.type) {
      case XS:
	xs += val; break;
      case YS:
	ys += val; break;
      case CS:
	cs += val; break;
      }
      isTerm = false;
    }
  }
  void print() {
    printf("%dy+%dx+%d=0", ys, xs, cs);
  }
  void multiply(int val) {
    xs *= val;
    ys *= val;
    cs *= val;
  }
  void subst(Eq ot) {
    xs -= ot.xs;
    ys -= ot.ys;
    cs -= ot.cs;
  }
  Eq clone() {
    Eq c;
    c.xs = xs;
    c.ys = ys;
    c.cs = cs;
    return c;
  }
  bool isSingleVar() {
    return (xs != 0 && ys == 0) || (xs == 0 && ys != 0);
  }
  int whichSingleVar() {
    if(xs != 0) return XS;
    return YS;
  }
  int varStatus() {
    if(isSingleVar()) return whichSingleVar();
    if(xs == 0 && ys == 0) return IS_NONE;
    return IS_COMPOUND;
  }
  bool isPossible() {
    return cs == 0;
  }
  ii getSingleVarSolution() {
    int var = (xs != 0)? xs : ys;
    int c = -1*cs;
    int g = gcd(abs(var), abs(c));

    if(var < 0){
      var *= -1;
      c *= -1;
    }

    var /= g;
    c /= g;
    return ii(var, c);
  }
  void printSingleVarSolution() {
    ii sol = getSingleVarSolution();

    printf("%d", sol.second);
    if(sol.first != 1)
      printf("/%d", sol.first);
    printf("\n");
  }
};


int main(){
  string line;
  int tc;
  getline(cin, line);
  stringstream ss(line); ss >> tc;

  for(int t = 0; t<tc; t++){
    if(t > 0) printf("\n");
    Eq e1, e2;
    getline(cin, line);
    e1.parse(line);

    if(TEST) {
      printf("Eq 1:\n%s\n", line.c_str());
      e1.print();
      printf("\n");
    }
    
    getline(cin, line);
    e2.parse(line);

    if(TEST){
      printf("Eq 2:\n%s\n", line.c_str());
      e2.print();
      printf("\n");

      printf("Types: %d %d\n", e1.varStatus(), e2.varStatus());
    }


    if((e1.varStatus() == IS_NONE && !e1.isPossible()) || (e2.varStatus() == IS_NONE && !e2.isPossible())) {
      printf("don't know\ndon't know\n");
    } else if(e1.varStatus() == IS_NONE && e2.varStatus() == IS_NONE){
      if(TEST){printf("case 1\n");}
      printf("don't know\ndon't know\n");
    } else if(e1.varStatus() == XS && e2.varStatus() == IS_NONE){
      if(TEST){printf("case 2\n");}
      e1.printSingleVarSolution();
      printf("don't know\n");
    } else if(e1.varStatus() == YS && e2.varStatus() == IS_NONE) {
      if(TEST){printf("case 3\n");}
      printf("don't know\n");
      e1.printSingleVarSolution();
    } else if(e2.varStatus() == XS && e1.varStatus() == IS_NONE) {
      if(TEST){printf("case 4\n");}
      e2.printSingleVarSolution();
      printf("don't know\n");
    } else if(e2.varStatus() == YS && e1.varStatus() == IS_NONE) {
      if(TEST){printf("case 5\n");}
      printf("don't know\n");
      e2.printSingleVarSolution();
    } else if(e1.varStatus() == XS && e2.varStatus() == XS) {
      if(TEST){printf("case 6\n");}
      ii s1 = e1.getSingleVarSolution();
      ii s2 = e2.getSingleVarSolution();
      if(s1 != s2) {
	printf("don't know\n");
	printf("don't know\n");
      } else {
	e1.printSingleVarSolution();
	printf("don't know\n");
      }
    } else if(e1.varStatus() == YS && e2.varStatus() == YS) {
      if(TEST){printf("case 7\n");}
      ii s1 = e1.getSingleVarSolution();
      ii s2 = e2.getSingleVarSolution();
      if(s1 != s2) {
	printf("don't know\n");
	printf("don't know\n");
      } else {
	printf("don't know\n");
	e1.printSingleVarSolution();
      }
    } else {
      if(TEST){printf("case 8\n");}
      if(e1.xs*e2.ys == e1.ys*e2.xs) {
	if(TEST){printf("case 9\n");}
	printf("don't know\ndon't know\n");
      } else {
	Eq c1 = e1.clone();
	Eq c2 = e2.clone();

	// Solve xs
	c1.multiply(e2.ys);
	c2.multiply(e1.ys);

	if(e1.varStatus() == XS) {
	  c1.subst(c2);
	  c1.printSingleVarSolution();
	} else {
	  c2.subst(c1);
	  c2.printSingleVarSolution();
	}

	// solve ys
	c1 = e1.clone();
	c2 = e2.clone();
	
	c1.multiply(e2.xs);
	c2.multiply(e1.xs);

	if(e1.varStatus() == YS) {
	  c1.subst(c2);
	  c1.printSingleVarSolution();
	} else {
	  c2.subst(c1);
	  c2.printSingleVarSolution();
	}
      }
    }
    
    getline(cin, line);
  }
}
