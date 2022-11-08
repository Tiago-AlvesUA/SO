#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "delays.h"
#include "process.h"

int main(void)
{
    printf("I'm the child: PID = %d, PPID = %d\n", getpid(), getppid());
    usleep(100000); //Aumentar para só aparecer prox msg quando o processo pai morrer.
    // Alínea (d), ativar o wait(), o processo pai espera pela conclusão do filho
    printf("I'm the child: PID = %d, PPID = %d\n", getpid(), getppid());

   return EXIT_SUCCESS;
}
