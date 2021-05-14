
// exercicio 6 lista 1

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
// passagem do nome do arquivo como parâmetro
int main(int nArgumentos, char ** Argumentos)
{
	// testa o numero de argumentos passado para o programa
	// se nao passou nenhum argumento erro
	if( nArgumentos == 1 ){
		printf("%s:numero de argumentos invalidos\n",Argumentos[0]);
		return 1;
	}


	FILE *fp; // ponteiro para o arquivo
	// abre um arquivo fazendo chamada de sistema ao SO
	// funcao fopen recebe 2 parametros:
	// 1 - nome do arquivo
	// 2 - modo de leitura - r somente leitura
	fp = fopen(Argumentos[1], "r");
	// testa se o arquivo foi aberto corretamente
	if( fp == NULL ){
		printf("%s:erro na aberto do arquivo %s\n",Argumentos[0], Argumentos[1]);
		return 1;
	}
	// le os caracteres do arquivo e imprime na tela(monitor) do interpretador
	// testa se não eh fim de arquivo
	while( !feof(fp)){
		// le um carcter do arquivo
		char c = fgetc(fp);
		printf("%c",c);
	}

	// fecha o arquivo de entrada
	fclose(fp);


}


