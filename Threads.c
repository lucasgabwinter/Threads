#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



// cada thread vai executar esta função
void *print_hello (void *palavra)
{
	char *cp = (char *) palavra;
	//estabelecendo o tempo
    time_t tempo = time(NULL) + 5;
    char atual[99];
    //esta cópia permite que a palavra não seja substituída a cada novo thread
    strcpy(atual,cp);
	//printando a palavra 10 vezes, durante 5 segundos
    while(time(NULL) < tempo) { 
		printf("%s", atual);
		printf("\n");
		printf("%s", atual);
		printf("\n");
		sleep(1);
	}
	pthread_exit (NULL);	// encerra este thread
}



// thread "main"
int main (void){
	long status;
	//criando um vetor de threads
	pthread_t t1[99];
	char palavra[99];
	printf("Digite 'sair' para encerrar ou outra palavra para criar um thread\n");
	gets(palavra);
	palavra[strlen(palavra)] = '\0';
	int i = 0;

	while(strcmp(palavra,"sair") != 0){
		status = pthread_create (&t1[i], NULL, print_hello, (void *)palavra);
		if (status) // ocorreu um erro
		{
			perror ("pthread_create");
			exit (-1);
		}
		printf("Digite 'sair' para encerrar ou outra palavra para criar um thread\n");
		gets(palavra);
		palavra[strlen(palavra)] = '\0';
		i++;
	}
	
	// encerra a thread "main"
	pthread_exit (NULL);
}
