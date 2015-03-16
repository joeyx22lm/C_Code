/*
* Phi / Euler's Totient written in C
* 3/16/2015 - Joseph Orlando
*/
static long phi(unsigned long input) {
   long current = 1,i,pow;
   for (i = 2; input != 1; i++){
      pow = 1;
      if(!(input%i)){
         input /= i;
         pow *= i;
      }
      current *= (pow - (pow/i));
   }
   return current;
}
