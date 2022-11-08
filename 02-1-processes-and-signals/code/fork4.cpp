#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "delays.h"
#include "process.h"

int main(void)
{
  printf("Before the fork: PID = %d, PPID = %d\n", getpid(), getppid());

  pid_t ret = pfork();
  if (ret == 0)
  {
	  //NECESSARIO COBRIR O ERRO, feito com o if
	  //exec serve para associar um programa diferente ao processo (processo child)
    if(execl("./child", "./child", NULL) == -1)
	{
		perror("child launching failed");
		exit(1);
	}
		
    printf("why doesn't this message show up?\n");
    return EXIT_FAILURE;
  }
  else
  {
    printf("I'm the parent: PID = %d, PPID = %d\n", getpid(), getppid());
    usleep(20000);
    pwait(NULL); //---> PROCESSO PAI espera pelo FIM DO PROCESSO FILHO com o wait
    // LOGO mesmo pondo o sleep entre mensagens do processo child, ele vai esperar.
  }

  return EXIT_SUCCESS;
}
