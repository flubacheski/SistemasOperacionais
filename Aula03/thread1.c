/*
  arquivo: thread1_win.c
  descricao: cria threads para imprimir valores de 0 ateh 999
*/

#include <windows.h>
#include <stdio.h>

/*
 	funcao que eh convertido em threads
*/
int imprimir_msg(char *nome)
{
    int i=0;

    for( i = 0; i < 100; i++)
        printf("%s thread - %d\n", nome, i);

    printf("%s thread terminada - %d\n", nome,i);

    return i;
}

int main()
{
    HANDLE handle[2]; // descritor das threads criadas
    DWORD id1,id2;     // identificador das threads
    char ch;

    printf("Programa de testa threads no windows\n");

   /*
     Cria nova thread e dispara sua execucao imediatamente
     apos ao retorno da funcao
     parametros

		HANDLE CreateThread(
			LPSECURITY_ATTRIBUTES lpThreadAttributes,
			DWORD dwStackSize,
			LPTHREAD_START_ROUTINE lpStartAddress,
			LPVOID lpParameter,
			DWORD dwCreationFlags,
			LPDWORD lpThreadId
	    );

� 	- lpThreadAttributes: Atributos de seguran�a da thread.
		Se for passado o valor NULL
		s�o assumidos os atributos padr�es;
�
	- dwStackSize: define a dimens�o m�xima do stack associado
	  � thread.Quando for 		passado zero como valor
	  deste argumento o limite default do stack 1Mb;

�	- lpStartAddress e lpParameter: definem, respectivamente, o endere�o da
		fun��o que a nova thread vai executar e o endere�o do argumento que ser� passado a essa fun��o;
�
	- dwCreationFlags: controla a cria��o da thread. Quando o seu valor � zero, a thread
		come�a a executar-se imediatamente a seguir � sua cria��o; e
�
	- lpThreadId: Endere�o do identificador atribu�do pelo SO a nova thread. N�o pode
		ser passado NULL.

	A fun��o devolve, em situa��o de falha, o valor 0, em caso de sucesso �
		devolvido o descritor da thread.

   */
    printf("Disparando primeira thread\n");
    handle[0] = CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)imprimir_msg, "Primeira", 0, &id1);

    printf("Disparando segunda thread\n");
    handle[1] = CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)imprimir_msg, "Segunda", 0, &id2);

    printf("\n");

    printf("\nPressione uma tecla para finalizar a processo\n");
    getch();
	printf("\nTerminando processo\n");

}
