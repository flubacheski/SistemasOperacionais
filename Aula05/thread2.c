#include <stdio.h>
#include <pthread.h>

int ret;

void * filho1( void * arg )
{
   
   printf ("\n[Filho 1] Meu pid = %d igual ao do meu pai = %s", getpid(), arg);
   printf ("\n[Filho 1] Vou esperar por 3s. ");
   fflush(stdout);
   sleep(1);
   sprintf(arg,"%s","OK");
   ret = 1;
   return  arg;
}



int main()
{
   	  pthread_t fid1;
        
        int  pid, v;
        char str_msg[10];
        char *retvalor;
	
        
        pid = getpid();
        printf ("\n[Pai  ] Chamada a funcao pthread_create. ");
        fflush(stdout); // garante que o buffer de stdout seja esvaziado


        // agora temos 2 threads  um filho e um pai;
        sprintf( str_msg,"%d",pid);
        
        v = pthread_create( &fid1, NULL, filho1, (void*)str_msg );
        if (v)
        {
                printf("\n[Pai    ] Erro na criacao da thread filho.");
                exit(1);
        }

        printf ("\n[Pai  ] Meu pid = %d", getpid());
        printf ("\n[Pai  ] Vou esperar meu filho terminar.");
        fflush(stdout);

        pthread_join(fid1,(void**) (&retvalor));
        printf ("\n[Pai  ] Meu filho %s terminou. \n",(char*) retvalor);
        return (1);
}
