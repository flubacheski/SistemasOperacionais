#include <stdio.h>
#include <stdlib.h>

int main () {
   int i, n;
   time_t t;
   
   n = 5;
   tor */
   // Inicializa gerador de numeros randomicos (aleatorios)
   // comente para ver o que acontece
   srand((unsigned) time(&t));

   
   // imprime 5 numeros randomicos de 0 a 49
   for( i = 0 ; i < n ; i++ ) {
      printf("%d\n", rand() % 50);
   }
   
   return(0);
}