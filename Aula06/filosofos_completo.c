/*
  Arquivo .:  filosofos.c
  Autor....:  Fabio Lubacheski
*/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>


#define N  5 // numero de filosofos

// vetor de garfos
sem_t  palito[N]; // semaforo contador para verificar o numero de
sem_t  mesa;

void myDelay( void )
{
   int j, r, i=0;
   time_t t;
   // Inicializa o gerador de numeros randomicos
   srand((unsigned) time(&t));

   r = rand()/10;
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
    sem_wait( &mesa );

    sem_wait(&palito[i]);
    sem_wait(&palito[(i+1)%N]);

    comendo(i);

    sem_post(&palito[i]);
    sem_post(&palito[(i+1)%N]);
    sem_post( &mesa);

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
    //sem_init (&semaforo, SHARED, valor_inicial)
    sem_init (&palito[i], 0, 1);
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

  // desaloca os semaforos
  for( i = 0; i < N; i++ ){
    sem_destroy(&palito[i]);
  }

  sem_destroy( &mesa );

  printf("\nFim do programa ...\n");
  return 1;
}

