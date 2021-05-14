#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

/***************************************************************

                         ShmDef

 Permite definir uma area de memoria compartilhada entre o processo
 pai e os processos filhos.

 Parametros:
 	size: comprimento da area de memoria compartilhada em Bytes. Este
	parametro deve ter valor superior a zero.
	descr: descritor que identifica a area de memoria compartilhada
	que foi criada.
 Saida
	Em caso de sucesso a funcao devolve um apontador para
	uma area de memoria compartilhada.
	Em caso de erro eh devolvido um apontador para NULL,
	o parametro descr retorna o valor do descritor da memoria
	compartilhada.
 Problemas e Limitacaes:
 	Esta funcao permite apenas definir uma area de memoria
	compartilhada entre o processo pai e os seus filhos.


***************************************************************/
void *ShmDef(int size, int *descr)
{
 int 	descritor;
 int 	f;
 void 	*tst;


 /*
    int shmget( key_t key, int size, int shmflg )
    
    key - chave de criacao (IPC_PRIVATE)
    
    size - dimensao do bloco
    
    shmflg - permissoes do bloco (EM OCTAL) combinadas com operador |
    
       IPC_CREAT cria bloco
       IPC_EXCL  devolve erro se o bloco jah existir
 
    
    funcao devolve um descritor ou -1 caso de erro.
   
 
 */
 
 
 //obtem de um descritor para a area de memoria compartilhada
 descritor = shmget(IPC_PRIVATE, size, IPC_CREAT|0600);
 if (descritor == -1)
 {
	perror("Erro em shmget, ao alocar memoria compartilhada!");
	return(NULL);
 }
 else
 {
	/*
      void * shmat( int shmid, char *shmaddr int shmflg );
      
      shmid - identificador (descritor) da memoria, obtido anteriormente por shmget

      shmaddr - endereco virtual a partir do qual comeca o bloco,  Se NULL o SO
         		 se encarrega de encontrar um endereco adquado
      
      shmflg  - opcoes:
         		 0 sem opcoes
                SHM_RDONLY somente para leitura
                SHM_RND    Arredonda o endereco no caso de shmaddr = NULL
   
      
      em caso de sucesso a funcao devolve o ponteiro void para o inicio do bloco, 
      caso contrario a funcao devolve NULL
   
   */
   
   
   /* Obten�o do apontador para a area de memoria comcompartilhada */
	tst = (void *) shmat(descritor, NULL, 0);
	if ((int)tst == -1)
 	{
		perror("Erro em shmat, ao alocar memoria compartilhada!");
		return(NULL);
 	}

 } // fim do if
 *descr = descritor;
 return(tst);
}

/***************************************************************

                         ShmDel

 Permite liberar a area de memoria compartilhada. Note que area
 soh eh removida quando mais nenhum processo a estiver utilizando


 Parametros:
 	descr: descritor identifica a area de memoria compartilhada
	para ser liberada.
 Saida
	Em caso de sucesso a funcao devolve o valor zero.
	Em caso de erro �devolvido o valor -1.


***************************************************************/
int ShmDel(int descr)
{
 int res;

 res = shmctl(descr, IPC_RMID, NULL);
 if (res == -1)
 {
	perror("Erro em ShmDel!");
 }
 return(res);

}
