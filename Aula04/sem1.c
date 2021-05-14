#include <stdio.h>
#include <stdlib.h>
#include "semlib.h"

int main()
{
      	pid_t pid;
        int s; // Descritor do semaforo
        
	s = SemDef( 0 );

        if( s == - 1 ){
	   printf("[Pai  ] Erro na alocacao do semaforo.\n");
           fflush(stdout);
           exit(1);
        }

        printf ("[Pai  ] Cria o processo filho. \n");
        fflush(stdout);

        pid = fork(); 

        // agora temos 2 processsos um filho e um pai        
        if (pid<0)
        {
           printf("[Pai  ] Erro na criacao do processo filho.\n");
           fflush(stdout);
           exit(1);
        }
        else if (pid == 0) // processo filho
        {
           printf("[Filho] Aguarda a liberacao pelo pai.\n");
           fflush(stdout);
           SemWait( s );

	   printf("[Filho] finaliza sua execucao.\n");
           /*	
           * O que acontece se liberacao do semaforo for realizada pelo
           * processo pai
           */
           if( SemDel( s ) == -1){
              printf("[Filho] Erro na liberacao do semaforo.\n");  
              fflush(stdout);
              exit(1);
           }
   
        }
        else{ // processo pai 
           
             sleep(5);
	     SemSignal( s );
	   
	     printf("[Pai  ] processo finalizado.\n");
             fflush(stdout);
	}

        
        return 1;
}
