import java.util.Scanner;
import java.util.List;
import java.util.ArrayList;
import java.math.BigInteger;
import java.util.HashMap;

class L {
    public static int test = 0;
    public static void printListI(List<Integer> L){
	for(int i = 0; i<L.size(); i++){
	    System.out.printf("%d ", L.get(i));
	}System.out.println();
    }
    public static void printListB(List<BigInteger> L) {
	for(int i = 0; i<L.size(); i++){
	    System.out.printf("%d ", L.get(i));
	}System.out.println();
    }
}

class Operator {
    public static BigInteger TWO = new BigInteger("2");
    public static BigInteger MAXV;
    private List<BigInteger> primes;
    Operator(){
	MAXV = pow(TWO, new BigInteger("63"));
	genPrimes();
	fac = new ArrayList<BigInteger>();
	fac.add(BigInteger.ONE);
    }
    private List<BigInteger> fac;
    BigInteger factorial(int n){
	while(n >= fac.size()){
	    BigInteger nxt = fac.get(fac.size()-1).multiply(new BigInteger(""+fac.size()));
	    fac.add(nxt);
	}
	return fac.get(n);
    }
    private void genPrimes(){
	primes = new ArrayList<BigInteger>();
	BigInteger total = BigInteger.ONE;
	for(int i = 2; true; i++) {
	    BigInteger nxt = new BigInteger(""+i);
	    if(isPrime(nxt)){
		total = total.multiply(nxt);
		primes.add(nxt);
		if(total.compareTo(MAXV) >= 0){
		    if(L.test >= 1)
			System.out.printf("Prime %d out of bounds,\n%d (product)\n%d (max value)\n", nxt, total, MAXV);
		    break;
		}
	    }
	}
	if(L.test >= 1){
	    L.printListB(primes);
	}
    }
    private BigInteger pow(BigInteger a, BigInteger p){
	if(p.equals(BigInteger.ZERO)) return BigInteger.ONE;
	if(p.equals(BigInteger.ONE)) return a;

	BigInteger sqr = pow(a, p.divide(TWO));
	if(p.mod(TWO).equals(BigInteger.ONE))
	    return sqr.multiply(sqr.multiply(a));
	return sqr.multiply(sqr);
    }
    private boolean isPrime(BigInteger x){
	if(x.equals(TWO)) return true;
	if(x.mod(TWO).equals(BigInteger.ZERO)) return false;
	for(BigInteger p = new BigInteger("3"); p.multiply(p).compareTo(x) < 0; p = p.add(TWO)){
	    if(x.mod(p).equals(BigInteger.ZERO)) return false;
	}
	return true;
    }
    BigInteger getProduct(List<Integer> pRep){
	BigInteger res = BigInteger.ONE;
	for(int i = 0; i<pRep.size(); i++){
	    for(int j = 0; j<pRep.get(i); j++){
		res = res.multiply(primes.get(i));
	    }
	}
	return res;
    }
    BigInteger getCombinations(List<Integer> pRep){
	Integer sum = 0;
	for(int i = 0; i<pRep.size(); i++){
	    sum += pRep.get(i);
	}
	BigInteger ans = factorial(sum);
	for(int i = 0; i<pRep.size(); i++){
	    ans = ans.divide(factorial(pRep.get(i)));
	}
	return ans;
    }
}

class Solver {
    private Operator op;
    private HashMap<BigInteger, BigInteger> solutions;
    private int total;
    Solver(){
	total = 0;
	op = new Operator();
	solutions = new HashMap<BigInteger, BigInteger>();
	predoSolutions();
	if(L.test >= 1){
	    System.out.printf("Total: %d\n", total);
	}
    }
    private void saveSolution(BigInteger combinations, BigInteger product){
	total++;
	if(L.test >= 2){
	    boolean BC = combinations.compareTo(op.MAXV) >= 0;
	    boolean BP = product.compareTo(op.MAXV) >= 0;
	    if(BC)
		System.out.printf("%d (combinations)\n%d (maxv)\n", combinations, op.MAXV);
	    if(BP)
		System.out.printf("%d (product)\n%d (maxv)\n", product, op.MAXV);
	    if(L.test >= 3) {
		System.out.printf("Save solution\n%d (combinations) => %d (product)\n", combinations, product);
	    }
	}
	BigInteger prev = solutions.get(combinations);
	if(prev == null)
	    solutions.put(combinations, product);
	else
	    solutions.put(combinations, prev.min(product));
    }
    private void predoSolutions(){
	saveSolution(BigInteger.ONE, op.TWO);
	
	List<Integer> ms = new ArrayList<Integer>();
	ms.add(0); ms.add(1);

	while(true){
	    // Generate until out of bounds
	    while(saveNext(ms)){}
	    // Get first breaking point
	    int i = 0;
	    for(; i<ms.size()-1; i++){
		if(ms.get(i) != ms.get(i+1)) break;
	    }
	    if(i == ms.size()-1){ // all were equal
		if(ms.get(0) == 1) break; // If product of first n primes is greater than MAXV, then the product of the first n+1 primes is also greater
		ms.set(0, 0);
		for(int j = 1; j<ms.size(); j++)
		    ms.set(j, 1);
		ms.add(1);
	    } else {
		int nextV = ms.get(i+1)+1;
		ms.set(0, nextV-1);
		for(int j = 1; j <= i+1; j++)
		    ms.set(j, nextV);
	    }
	    
	}
    }
    private boolean saveNext(List<Integer> lst){
	lst.set(0, lst.get(0)+1);

	BigInteger combs = op.getCombinations(lst);
	BigInteger prod = op.getProduct(lst);

	boolean valid = prod.compareTo(Operator.MAXV) < 0;
	if(valid)
	    saveSolution(combs, prod);

	if(L.test >= 2) {
	    L.printListI(lst);
	}

	return valid;
    }
    BigInteger getSolution(BigInteger x){
	return solutions.get(x);
    }
}

public class Factors {
    public static void main(String[] args){
	Solver s = new Solver();

	Scanner in = new Scanner(System.in);

	while(in.hasNextBigInteger()){
	    BigInteger nxt = in.nextBigInteger();
	    BigInteger sol = s.getSolution(nxt);
	    if(sol == null) while(true){}
	    System.out.printf("%d %d\n", nxt, s.getSolution(nxt));
	}
    }
}
