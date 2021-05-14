/* arquivo: thread1.c
*  descricao: Programa para teste de threads. Utiliza a biblioteca pthreads.
*  para compilar:  gcc -g thread1.c -lpthread -o thread1
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void myDelay( void )
{
   int j, r,i;
   r= random()/(10);
   for( j = 0; j < r; j++)
        i++;
}
/*
 Processo que e'convertido em threads
*/
int imprimir_msg(char *nome)
{
   int i=0;

   for( i = 0; i < 100; i++){
      printf("Thread %s - %d\n", nome, i);
      myDelay();
   }
   printf("Thread %s terminado \n", nome);
   return i;
}

int main()
{
   pthread_t id1;
   pthread_t id2;
   int ret;

   printf("Programa de teste de pthreads \n");

   /*
     Cria nova thread e dispara sua execucao imediatamente
     apos ao retorno da funcao
     paramentros
        1 - endereco da variavel que guardara o id da thread
        2 - conjunto de atributos do tipo pthread_attr_t. O valor
            NULL indica o uso de valores default
        3 - nome da funcao que sera' executada
        4 - o endereco da variavel que sera passada como
             parametro para a funcao
   */
   printf("Disparando primeira thread\n");
   pthread_create(&id1, NULL, (void*) imprimir_msg,"thread_1");

   printf("Disparando segundo thread\n");
   pthread_create(&id2, NULL, (void*) imprimir_msg,"thread_2");

   // comente a partir daqui

   pthread_join(id1,(void*)&ret);
   printf("valor do retorno %d\n",ret);


   pthread_join(id2,NULL);
   printf("Terminando processo\n");


}
