/*
  Arquivo .:  prod_cons_win.c
  Autor....:  Fabio Lubacheski

  Exemplo da implementação do programa classico Produtor-Consumidor usando pthreads no Linux
  Uma par de threads se comunicam atraves de um buffer de 5 posicoes.
  A primeira thread denomidada Produtor, produz itens e os coloca no
  buffer. A segundo thread denominada Consumidor retira os items e os imprime.
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>


/*
	Recursos compartilhados
*/

#define N 5
// variáveis compartilhadas
int buffer[N], true=1;
//declaração dos semáforos contadores
sem_t SemProdutor;
sem_t SemConsumidor;


#define IM 139968
#define IA 3877
#define IC 29573

double gen_random(double max) {
    static long last = 42;

    last = (last * IA + IC) % IM;
    return( max * last / IM );
}

void myDelay( void )
{
   int j, r, i=0;
   r = gen_random(100000000);
   for( j = 0; j < r; j++)
        i++;
}
int produz(){
	 // Inicializa o gerador de numeros randomicos
   myDelay();
   int valor=gen_random(50);
   printf("\nproduzido:%d",valor);
   return (valor);
}
void consome(int valor){
  myDelay();
	printf("\nconsumido:%d",valor);
}

void Produtor()
{
	int f=0;
	while( true ){
		sem_wait(&SemProdutor);
		buffer[f]=produz();
		f = (f+1)%N;
		sem_post(&SemConsumidor);
	}
	printf("\n[Produtor  ] terminado!\n");
}
void Consumidor(){
	int i=0;
	while( true ){
		sem_wait(&SemConsumidor);
		consome(buffer[i]);
		i = (i+1)%N;
		sem_post(&SemProdutor);
	}
}
int main()
{
	pthread_t idProdutor, idConsumidor;
	// inicialização do semaforo
	sem_init(&SemProdutor, 0, N);
	sem_init(&SemConsumidor, 0, 0);


	pthread_create(&idProdutor, NULL,(void*)Produtor, NULL);
	pthread_create(&idConsumidor, NULL,(void*)Consumidor, NULL);


	// Espera as threads terminarem
	pthread_join(idProdutor,NULL);
	pthread_join(idConsumidor,NULL);
	printf("\nProcesso Principal Terminado!\n");
	return (1);
}
