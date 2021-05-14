#include <sys/types.h> 
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/* 
   Exemplo de criacao de processos
   A funcao fork() cria um processo filho identico ao pai, exceto pelo PID. 
   Caso tenha sucesso o processo pai recebe o PID do filho criado e no processo 
   filho comeca com o valor zero. Em  caso de erro a funcao fork() devolve -1 ao 
   processo pai e o filho não é criado.


   Autor......: Fabio Lubacheski


   Observacao: fflush( stdout )
              forca a escrita dos buffers da memoria para a stream especificada
              fazer o exemplo sem fflush e com fflush
*/


int main()
{
        int pid_pai, pid;
        // pega o pid do processo corrente
        pid_pai = getpid();

        printf ("\n[Pai  ] pid=%d Chamada a funcao fork. ",pid_pai);
        fflush(stdout);

        // na linha debaixo cria um novo processo, duplicando o processo pai e criando o
		// processo filho
        pid = fork(); 
    
        // agora temos 2 processsos um filho e um pai
		// O valor do retorno do fork eh seguinte:
		// o processo pai recebe o pid do processo filho na variavel pid
		// o processo filho recebe o valor zero na variavel pid
		// caso ocorra falha o n�o eh criado o processo filho
		// o eh valor da variavel pid eh negativo
        if (pid<0)
        {
           printf("\n[Pai  ] Erro na criacao do processo filho.");
           fflush(stdout);
           exit(1);
        }
        else if (pid == 0) // processo filho
        {
           printf ("\n[Filho] Meu pid = %d. Pid do meu pai = %d variavel pid=%d", getpid(), pid_pai, pid);
           fflush(stdout);
			  
				
        }
        else{
           printf ("\n[Pai  ] Meu pid = %d. Pid do meu filho = %d(variavel pid)", pid_pai, pid);
           fflush(stdout);
			
         
        } 
        printf ("\nProcesso Nr [%d ] Finalizou.\n", getpid());
        fflush(stdout);
        return (1);
}

