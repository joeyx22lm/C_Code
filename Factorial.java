import java.io.*;
import java.util.Scanner;
public class Factorial
{
  // factorial through iteration
  public static long factorial(long N){
    // start @ value of N
    long Value = N;
    for(int i = N; i > 0; i--){
      // multiply current sum of values by N
      // unless N = 0, in which case don't do it!
      Value = (Value * N);
    }
    return Value;
  }
  
  // factorial through recursion
  public static long factorial(long n){
      return ((n<2) ? 1 : (n * factorial(n-1)));
  }

  public static void main(String [] args){
    System.out.println("Factorial of: ");
    Scanner s = new Scanner(System.in);
    long N = s.nextLong();
    long Factorial = factorialR(N);
    System.out.println("Factorial of " + Long.valueOf(N) + " = " + Long.valueOf(Factorial));
  }
}
