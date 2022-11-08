#include <stdio.h>
#include <unistd.h>

#include "thread.h"

void *thread_main(void * arg){
	int max = 10;
	if (arg != NULL)
		max = *((int*)arg);
	for (int i = 1; i <= max; i++){
		printf("%3d\n", i);
		usleep(1000000);
	}
	return NULL;
}

int main(int argc, char*argv[]){
	pthread_t my_thread;
	
	// da forma em que não é preciso tratar os erros:
	// (se usássemos p_thread create e join era preciso tratar os erros)
	thread_create(&my_thread, NULL, &thread_main, NULL); //Passa-se a função thread_main, sem argumentos
	
	thread_join(my_thread, NULL);

	return 0;
}

