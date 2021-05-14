
/*
	Exemplo de geracao de numeros randomicos

*/

#include <stdio.h>

#define IM 139968
#define IA 3877
#define IC 29573

double gen_random(double max) {
    static long last = 42;

    last = (last * IA + IC) % IM;
    return( max * last / IM );
}


void main( void )
{
	int nrand,i;
	printf("Gera 10 numeros randomicos de 0 ateh 1000\n\n");
	for( i = 0 ; i < 10; i++)
		printf("Order %2d: [%d]\n",i+1, (int)gen_random(1000));

}


