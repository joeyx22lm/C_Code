// global library
#include <stdio.h>

// projecteuler.net: problem 1
// find the sum of all multiples
// of 3 and 5 from 1 to 1000
int problemOne(){
   int ceiling = 1000;
   int sum = 0;
   for(int i = 1; i<ceiling;i++){
      if((i%3)==0 || (i%5)==0){
         sum += i;
      }
   }
   printf("The sum of all multiples of 3 and 5, between 1 and %d is %d", ceiling, sum);
   return 1;
}


// projecteuler.net: problem 63 Powerful Digit Counts
// find numbers where n^m = a
// and a is m digits long.

// libraries for Problem 63
#include <stdlib.h>
#include <string.h>
#include <math.h>
int problem63(){
   intmax_t current = 0;
   char currentC[200];
   for(int a = 1; a<100;a++){
      for(int b = 1; b<100;b++){
         current = pow(a, b);
         sprintf(currentC, "%ld", current);
         if(strlen(currentC) == b){
            printf("%d ^ %d = %jd\n", a, b, current);
         }
      }
   }
   return 1;
}
