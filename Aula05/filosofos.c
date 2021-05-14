/*
  Arquivo .:  filosofos.c
  Autor....:  Fabio Lubacheski
*/

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <curses.h>


#define N  5 // numero de filosofos

// vetor de palitos
pthread_mutex_t  palito[N]; // semaforo contador para verificar o numero de filosofos comendo simultaneamente
sem_t 		 mesa;

void myDelay( void )
{
   int j, r,i;
   r= random()/(10);
   for( j = 0; j < r; j++)
        i++;
}

void pensando(int i)
{

   printf("filosofo [%d] pensando\n",i);
   myDelay();
}

void comendo(int i)
{

   printf("filosofo [%d] comendo\n",i);
   myDelay();
}

/*
*
* Processo que e'convertido em varias threads
*
*/
void  filosofo ( int *k )
{

  int i;
  i = *k;
  while( 1 ){
    pensando(i);
    //sem_wait( &mesa );

    pthread_mutex_lock(&palito[i]);
    pthread_mutex_lock(&palito[(i+1)%N]);

    comendo(i);

    pthread_mutex_unlock(&palito[i]);
    pthread_mutex_unlock(&palito[(i+1)%N]);

    //sem_post( &mesa);
  }

}


int main(void)
{

  char ch;
  int i;
  pthread_t id_filosofos[N];	  // ID das threads criadas
  int       ordem[N];

  /*
      inicializa os semaforos
  */
  for( i = 0; i < N; i++ ){
    //palito[i] = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_init(&palito[i],NULL);
  }

  sem_init( &mesa, 0, N - 1);

  // Imprime o Cabecalho do restaurante
  printf("Jantar dos filosofos\n");
  printf("pressione qualquer tecla para sair\n");

  // cria os filosofos
  for( i=0; i < N; i++ ){
         ordem[i]=i;
         pthread_create( &id_filosofos[i], NULL, (void*)filosofo,
         &ordem[i]);
  }

  scanf("%c",&ch);
  /*
      destroi os semaforos
  */
  for( i = 0; i < N; i++ ){
    pthread_mutex_destroy(&palito[i]);
  }
  sem_destroy( &mesa );


  printf("\nFim do programa ...\n");
  return 1;
}

