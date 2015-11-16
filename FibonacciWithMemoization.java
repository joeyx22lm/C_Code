/*
* @author: Joseph Orlando
* Dynamic Programming Fibonacci via Recursion
* with Memoization.
* 
* Expected Output:
*   0 1 1 2 3 5 8 13 21 34 55 89 144 233 377 610 987 1597 2584 4181 6765 10946 17711 28657 46368 75025 121393 196418 317811 514229 832040 1346269 2178309 3524578 5702887 9227465 14930352 24157817 39088169 63245986 102334155 165580141 267914296 433494437 701408733 1134903170 1836311903 -1323752223 512559680 -811192543
*   Without Memoization: 87897ms
*
*   0 1 1 2 3 5 8 13 21 34 55 89 144 233 377 610 987 1597 2584 4181 6765 10946 17711 28657 46368 75025 121393 196418 317811 514229 832040 1346269 2178309 3524578 5702887 9227465 14930352 24157817 39088169 63245986 102334155 165580141 267914296 433494437 701408733 1134903170 1836311903 -1323752223 512559680 -811192543
*   With Memoization: 9ms
*/
import java.util.HashMap;
public class FibonacciWithMemoization {
	private static HashMap<Integer, Integer> fibCache = null;
	public static int fibonacci(int n){
	    return((n <= 1) ? n : (fibonacci(n-1) + fibonacci(n-2)));
	}
	public static int fibonacciMemoized(int n){
		if((fibCache == null || fibCache.get(n) == null) && n <= 1){
			fibCache.put(n, n);
		}else if(fibCache == null || fibCache.get(n) == null){
			fibCache.put(n, (fibonacciMemoized(n-1) + fibonacciMemoized(n-2)));
		}
	    return fibCache.get(n);
	}	
	public static long currentTime(){
		 return System.currentTimeMillis();
	}
	public static void main(String[] args){
		long start = currentTime();
		for(int i = 0; i<50;i++){
			System.out.print(fibonacci(i) + " ");
		}
		System.out.println("\nWithout Memoization: " + (currentTime() - start) + "ms\n");
		fibCache = new HashMap<Integer, Integer>();
		start = currentTime();
		for(int i = 0; i<50;i++){
			System.out.print(fibonacciMemoized(i) + " ");
		}
		System.out.println("\nWith Memoization: " + (currentTime() - start) + "ms\n");
	}
}
