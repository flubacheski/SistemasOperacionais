/*
  Objetivo...:
     Em um restaurante existe um determinado numero de lugares para as
     pessoas comerem. Quando chega um cliente, se ha algum lugar vago, o
	  cliente entra no restaurante, para comer. Se não ha' lugar vago, o
	  cliente fica esperando do lado de fora. Quando um cliente termina 
	  de comer e sai do restaurante, o seu lugar fica vago, e outro cliente
	  esperando pode entrar. O restaurante nao controlaa a ordem de chegada
	  dos clientes, logo eles conseguem entrar em qualquer ordem, so e'
	  controlado o lugar ocupado pelo cliente. O Restaurante serve uma
	  quantidade fixa de Refeicoes quando acaba as refeicoes automaticamente
	  o restaurante fecha.

     Cada cliente e'um uma thread e sao criadas conforme solicitacao, por exemplo,
     pressionando uma tecla.

     Arquivo ...:	Restaurante.c
     Autor......: Fabio Lubacheski
*/

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>


#define OCUPADO 		0	// Cadeira ocupada
#define DESOCUPADO 	1	// Cadeira desocupada
#define N_LUGARES 	3 	// Define o numero de lugares
#define REFEICOES 	7	// Numero maximo de refeicoes servidas no restaurante
#define COMENDO		10 // tempo em segundos

/*
  numero de clientes comendo no momento
*/
int nClientesComendo=0;

int lugares[N_LUGARES];
/* 
   semaforo binario para exclusao mutua das variaveis compartilhadas
   inicializa a variavel semafaro mutex com valor default
*/
pthread_mutex_t  mutex=PTHREAD_MUTEX_INITIALIZER;  

sem_t		    lugar; 	// semaforo contador para os lugares no restaurante

void myDelay( void )
{
   int j, r,i;
   r= random();///10);
   for( j = 0; j < r; j++)
        i++;
}

/*
*
* Processo que e'convertido em varias threads
*
*/
void  cliente ( char *nome_cliente )
{

   int  k;		// guarda o lugar que o cliente vai sentar
   char nome;

   nome = *nome_cliente;

   /*
      Caso nao exista cadeiras desocupadas o cliente fica bloqueado
      no semaforo contador
   */
   if(  nClientesComendo >= N_LUGARES )
	  printf("O cliente '%c' vai esperar pois nao existe cadeiras desocupadas\n", nome);
   
	
   sem_wait( &lugar);

   /*
      incrementa o numero de clientes comendo ao mesmo tempo e
      procura um lugar para o cliente.
      
      trecho deve ser executado de forma initerruptamente, para garantir a
      consistencia das informacoes (Secao Critica)
      
      Para garantir isso deve ser utilizado a exclusao mutua, ou seja, quando algum processo (thread)
      estiver usando o recurso, os demais serao impedidos.
      Para implementar a exclusao mutua foi utilizado um semaforo binario.
      
      inicio da exclusao mutua
   */
   pthread_mutex_lock(&mutex);
	
   nClientesComendo++;
   
   for( k = 0; k < N_LUGARES;k++){
      if( lugares[k]==DESOCUPADO){
         lugares[k]=OCUPADO;
         break;
      }
   }
 
   /*
     fim da exclusao mutua
   */
   pthread_mutex_unlock(&mutex);

   printf("Cliente  '%c'  COMENDO no lugar %d\n", nome, k+1);

   /*
     tempo que o cliente fica comendo
   */
   myDelay();
   
   /*
    inicio da exclusao mutua
   */
   pthread_mutex_lock(&mutex);

   nClientesComendo--;
   lugares[k]=DESOCUPADO;

   /*
    termina a exclusao mutua
   */
   pthread_mutex_unlock(&mutex);

   printf("Cliente  '%c'  acabou de COMER no lugar %d !!\n", nome, k+1);


   /*
     avisa que desocupou o lugar onde estava comento
   */
   sem_post( &lugar);
   
}


int main(void)
{
	
   /*
    numero total de clientes( threads ) no restaurante
    O Clientes que ja comeram que estao esperando para
    comer e os que estao comendo
   */
   int  nClientes=0;		   
   
   pthread_t id_threads[REFEICOES];  // ID das threads criadas
   
   char	   nome_clientes[REFEICOES+1]; // Guarda o nome dos clientes

   char    ch, i;// tecla pressionada


   /*
    Todos os lugares estao desocupados
   */
   for( i = 0; i < N_LUGARES;i++)
      lugares[i] = DESOCUPADO;

	/*
     inicializa semaforo contador para sincronizar o uso de lugares
     parametro
        1 - endereco da variavel sem_t
        2 - 0 indica que o semaforo eh compartilhado entre as threads de um processo
        3 - valor para iniciar o semaforo
        
        nessa biblioteca todas as funcoes retornam 0 para sucesso e -1 para falha
   */
   sem_init( &lugar, 0, N_LUGARES);
   
   // Imprime o Cabecalho do restaurante
   printf("Restaurante Servira' %d refeicoes e conta com %d lugares\n", REFEICOES, N_LUGARES );
   printf("Digite qualquer LETRA para entrar um cliente.\n('z' Fecha o Restaurante):\n");

   // sai do laco quando o vetor de threads esta cheio ou
   // quando a letra Z eh pressionada
   for( ;; ){
	
	  //printf("Numero de refeicoes servidas : %d \n", nClientes);
	  //printf("Numero de Clientes comendo   : %d \n", ClientesComendo);
     scanf("%c",&ch);
	  fflush(stdin);
	  //ch = getc(stdin);
	
	  if(ch == 'Z' || ch == 'z')
	     break;

	  

	  // Verifica se terminou porque acabou as refeicoes ou se foi pedido para
	  if(isalpha( ch )){
         
         nome_clientes[nClientes] = ch;

         // verifica se é um caracter para o nome do cliente
         if( nClientes < REFEICOES ){
            // Atualiza o numero de clientes no restaurante
		      // e imprime avisando que o cliente ja esta esperando para
		      // comer
     
		      printf("O cliente  '%c'  chega ao Restaurante !\n",nome_clientes[nClientes]);
            /*
               Cria nova thread e dispara sua execucao imediatamente apos ao retorno da funcao
               paramentros
               1 - endereco da variavel que guardara o id da thread
               2 - conjunto de atributos do tipo pthread_attr_t. O valor
                  NULL indica o uso de valores default
               3 - nome da funcao que sera' executada
               4 - o endereco da variavel que sera passada como parametro para a funcao
                  
            */
         
            pthread_create( &id_threads[nClientes], NULL, (void*)cliente, &nome_clientes[nClientes]);
	        nClientes++;         }else{
            printf("Nao ha' mais refeicoes, o cliente '%c' foi embora."
	          "\nDigite a letra 'z' para sair!!\n\n", nome_clientes[nClientes]);
        }
     }
   }
   
   printf("O restaurante vai fechar aguarde! esperando os clientes terminar de comer . . .\n");
   /*
      sincroniza as threads que nao terminaram
   */
   for( i = 0; i < nClientes; i++ ){
      pthread_join(id_threads[i],NULL);
   }
   
   /*
      destroi os semaforos 
   */
   pthread_mutex_destroy(&mutex);
   sem_destroy( &lugar );
   
	
	printf("\nRestaurante fechou, bye bye\n");
	return 1;
}

