#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <ctype.h>


union semun
{
	int val;			// value for SETVAL
	struct semid_ds *buf;		// buffer for IPC_STAT & IPC_SET
	unsigned short int *array;	// array for GETALL & SETALL
	struct seminfo *__buf;		// buffer for IPC_INFO
};

/***************************************************************

                         SemDef

 Permite definir um semaforo

 Parametros:
 	valor_inicial: valor a que deve ser inicializado o semaforo.

 Saida
 	Descritor do semaforo
	-1 em caso de erro

 Problemas e Limitacoes:
 	Permite a utilizacao de semaforos comuns ao processo
	pai e os filhos.


***************************************************************/

int SemDef(int valor_inicial)
{
 int 	descr_sem;
 int 	erro;

  //Criacao do Semaforo
 descr_sem = semget(IPC_PRIVATE, 1, IPC_CREAT|0777);
 if (descr_sem == -1)
 {
	perror("Erro ao criar o semaforo!");
	return(-1);
 }

 // Inicializa o valor do semaforo
 erro = semctl(descr_sem, 0, SETVAL, valor_inicial);
 if (erro == -1)
 {
	perror("Erro ao atribuir valor inicial ao semaforo!");
	return(-1);
 }
 return(descr_sem);
}

/***************************************************************

                         SemSignal

 Implementa a primitiva de Signal que permite incrementar o
 valor do semaforo. Caso exista um processo suspenso este eh
 desbloqueado 

 Parametros:
 	descr_sem: descritor do semaforo

 Saida
 	0 em caso de sucesso
	-1 em caso de erro


***************************************************************/

int SemSignal(int descr_sem)
{
 struct sembuf 	aux;
 int 		erro;

 // Preenche a estrutura que permite operar sobre o semaforo
 aux.sem_num = 0;
 aux.sem_op = 1;
 aux.sem_flg = 0;

 // Excuta a opera�o
 erro = semop(descr_sem, &aux, 1);
 if (erro == -1)
 {
	perror("Erro em Signal!");
	return(-1);
 }

 // Em caso de sucesso da fun�o
 return(0);

}


/***************************************************************

                         SemWait

 Implementa a primitiva de Wait que permite decrementar o
 valor do semaforo. Caso este valor seja igual a zero o
 processo fica bloqueado.

 Parametros:
 	descr_sem: descritor do semaforo

 Saida
 	0 em caso de sucesso
	-1 em caso de erro

***************************************************************/

int SemWait(int descr_sem)
{
 struct sembuf 	aux;
 int 		erro;

 // Preenche a estrutura que permite operar sobre o semaforo
 aux.sem_num = 0;
 aux.sem_op = -1;
 aux.sem_flg = 0;

 // Excuta a opera�o
 erro = semop(descr_sem, &aux, 1);
 if (erro == -1)
 {
	perror("Erro em Wait!");
	return(-1);
 }

 // Em caso de sucesso da fun�o
 return(0);
}


/***************************************************************

                         SemDel

 Remove um semaforo do Kernel.

 Parametros:
 	descr_sem: descritor do semaforo

 Saida
 	0 em caso de sucesso
	-1 em caso de erro

***************************************************************/


int SemDel(int descr_sem)
{
 union semun aux;

 return(semctl(descr_sem, 0, IPC_RMID, aux));

}
