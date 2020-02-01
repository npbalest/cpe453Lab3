//From Tutorialspoint

#include <stdio.h>
#include <stdlib.h>

int main () {
   int i, n;
   time_t t;
   
   n = 1000000;
   
   /* Intializes random number generator */
   srand((unsigned) time(&t));

   /* Print 5 random numbers from 0 to 10000 */
   for( i = 0 ; i < n ; i++ ) {
      printf("%d\n", rand() % 10000);
   }
   
   return(0);
}