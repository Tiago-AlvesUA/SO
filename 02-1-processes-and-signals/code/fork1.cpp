#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "delays.h"
#include "process.h"

int main(void)
{
  printf("Before the fork:\n");
  printf("  PID = %d, PPID = %d\n", getpid(), getppid());
	//PID vai buscar número de identidade do processo;
	//Get PPID -> número do processo pai
	
  pfork();
	//pfork já tem a programação defensiva!
  
	// fork retorna 2 vezes, UMA PROCESSO PAI OUTRA PROC FILHO
	// Sabemos o ID do pai porque fizemos o before the fork (PID)
  printf("After the fork:\n");
  printf("  PID = %d, PPID = %d\n",getpid(), getppid());
  bwRandomDelay(0, 100000);
	// Propósito da fc é não libertar o CPU, ficando à espera
	// Ao aumentar o delay não sabemos distinguir de pai/filho
  printf("  Was I printed by the parent or by the child process? How can I know it?\n"); 
  
  return EXIT_SUCCESS;
}

