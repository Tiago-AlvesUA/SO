#include <stdio.h>
#include <unistd.h>

#include "thread.h"

void *thread_main(void* arg){
	int max = 10;
	if (arg != NULL)
		max = *((int*)arg);
	for (int i = max-9; i <= max; i++){
		printf("%3d\n", i);
		usleep(1000000);
	}
	return NULL;
}

int main(int argc, char*argv[]){

	int count = 10;
	pthread_t my_threads[5];
	for (int i = 0; i<5; i++)
	{
		thread_create(&my_threads[i], NULL, &thread_main, &count);
		thread_join(my_threads[i], NULL);
		count = count + 10;
	}
	return 0;
}
