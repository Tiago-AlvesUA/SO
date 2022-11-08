#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

#include "delays.h"
#include "process.h"

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		perror("Argument length is wrong, should be: g++ ki.cpp <<PID>>");
		exit(1);
	}
	
	int id = atoi(argv[1]);
	pkill((pid_t)idd,SIGINT);
	
	return EXIT_SUCCESS;S
}
