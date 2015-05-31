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
