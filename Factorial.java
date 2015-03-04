import java.io.*;
import java.util.Scanner;
public class Factorial
{
  public static long factorial(long N){
   long Value = 1;
   if(N > 1){
      Value = (N * factorial(--N));
   }
   return Value;
  }
  public static void main(String [] args){
    System.out.println("Factorial of: ");
    Scanner s = new Scanner(System.in);
    long N = s.nextLong();
    long Factorial = factorial(N);
    System.out.println("Factorial of " + Long.valueOf(N) + " = " + Long.valueOf(Factorial));
  }
}
