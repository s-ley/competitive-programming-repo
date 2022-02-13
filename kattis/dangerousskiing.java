import java.util.Scanner;
import java.math.BigDecimal;

public class dangerousskiing {
    static BigDecimal[][] DP, P;
    static BigDecimal n2 = new BigDecimal(-2);
    static BigDecimal n1 = new BigDecimal(-1);
    static int n;
    
    static void init(){
	DP = new BigDecimal[n][n];
	P = new BigDecimal[n][n];

	for(int i = 0; i<n; i++){
	    for(int j = 0; j<n; j++){
		DP[i][j] = n2;
		P[i][j] = n2;
	    }
	    DP[i][0] = BigDecimal.ONE;
	}
    }
    static BigDecimal f(int walks, int node) {
	if(walks < 0) return n1;
	if(!DP[walks][node].equals(n2)) return DP[walks][node];

	BigDecimal best = n1;
	for(int i = 0; i<n; i++){
	    if(i<node && !P[i][node].equals(n2)){
		BigDecimal p1 = f(walks, i);
		BigDecimal p2 = f(walks-1, i);
		if(!p1.equals(n1))
		    best = best.max(p1.multiply(P[i][node]));
		if(!p2.equals(n2))
		    best = best.max(p2);
	    } else if(node < i && !P[node][i].equals(n2)){
		best = best.max(f(walks-1, i));
	    }
	}

	DP[walks][node] = best;
	return best;
    }
    static void test(){
	for(int i = 0; i<n; i++){
	    for(int j = 0; j<n; j++){
		System.out.print(P[i][j]);
		System.out.print(" ");
	    }
	    System.out.println();
	}
    }
    public static void main(String[] args){
	Scanner sc = new Scanner(System.in);
	int m;
	n = sc.nextInt();
	m = sc.nextInt();
	init();

	// Save double value in DP, keep track of history
	// Multiply at the end with big decimal
	for(int i = 0; i<m; i++){
	    int a, b; BigDecimal c;
	    a = sc.nextInt();
	    b = sc.nextInt();
	    c = sc.nextBigDecimal();

	    if(a==b) continue;
	    
	    int st = Math.min(a,b);
	    int ed = Math.max(a,b);

	    P[st][ed] = BigDecimal.ONE.subtract(c);
	}

	for(int i = 0; i<n; i++){
	    if(i>0) System.out.print(" ");
	    BigDecimal ans = f(i, n-1);
	    if(ans.equals(n1))
		System.out.print("-1");
	    else
		System.out.print(ans);
	}
	System.out.println();
    }
}
